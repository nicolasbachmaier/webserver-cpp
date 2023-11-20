#include "headers.h"

const std::string Webserver::server = "Bachmaier Technology";
const std::string Webserver::strict_transport_security = "max-age=31536000; includeSubDomains"; // HSTS policy for one year including subdomains
const std::string Webserver::x_content_type_options = "nosniff"; // disable MIME type sniffing
const std::string Webserver::x_frame_options = "SAMEORIGIN"; // allow frame/iframe embedding from same origin only
const std::string Webserver::content_security_policy = "default-src 'self'; script-src 'self' 'unsafe-inline'; style-src 'self' 'unsafe-inline'"; // allow content loading from the same origin only
const std::string Webserver::x_xss_protection = "1; mode=block"; // enable XSS protection and block rendering if an attack is detected
const std::string Webserver::access_control_allow_origin = "*"; // allow any origin (this is a very permissive setting, and you might want to restrict it)
const std::string Webserver::access_control_allow_credentials = "true"; // allows cookies to be sent with CORS requests
const std::string Webserver::access_control_expose_headers = "Content-Length"; // exposes the Content-Length header to CORS requests
const int Webserver::HTTP_Port = 80;
const int Webserver::HTTPS_Port = 443;
std::unordered_map<int, int> Webserver::server_fd;
std::unordered_map<int, struct sockaddr_in> Webserver::address;
std::unordered_map<int, int> Webserver::addrlen;

std::mutex map_mutex;

void Webserver::initialize_socket(const int &port) {
    std::lock_guard<std::mutex> lock(map_mutex); // Thread-Safety
    // File Descriptor for the Server Socket (IPv4 Protocol + TCP)
    server_fd.insert(std::make_pair(port, socket(AF_INET, SOCK_STREAM, 0)));
    if (server_fd.at(port) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set socket to non-blocking mode
    int flags = fcntl(server_fd.at(port), F_GETFL, 0);
    if (flags < 0) {
        std::cerr << "Error getting socket flags" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (fcntl(server_fd.at(port), F_SETFL, flags | O_NONBLOCK) < 0) {
        std::cerr << "Error setting socket to non-blocking" << std::endl;
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    // Options at Socket Level
#ifdef __APPLE__
    // Set only SO_REUSEADDR
    if (setsockopt(server_fd.at(port), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt Error");
        std::cerr << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    if (setsockopt(server_fd.at(port), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt Error");
        std::cerr << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif
    struct sockaddr_in tmp_address{};
    tmp_address.sin_family = AF_INET; // Address Family: IPv4
    tmp_address.sin_addr.s_addr = INADDR_ANY; // Bind Socket to all available IP Interfaces
    tmp_address.sin_port = htons(port); // Set the Port - htons makes sure about the network byte order
    address.insert(std::make_pair(port, tmp_address));

    // Bind options to the Socket
    if (bind(server_fd.at(port), (struct sockaddr *) &address.at(port), sizeof(address.at(port)))) {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd.at(port), 999) < 0) { // Mark socket as passive + max. queue length for pending connections
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    addrlen.insert(std::make_pair(port, sizeof(address.at(port))));
}

void Webserver::start_webserver(const int &port) {
    initialize_socket(port);
    while (true) {
        int new_socket = accept(server_fd.at(port), (struct sockaddr *) &address.at(port),
                                (socklen_t *) &addrlen.at(port));
        if (new_socket < 0) {
            // Check for the specific non-blocking mode error
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                continue;
            } else {
                std::cerr << "Accept failed: " << strerror(errno) << std::endl;
                continue;
            }
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(address.at(port).sin_addr), client_ip, INET_ADDRSTRLEN);
        std::cout << "New connection from " << client_ip << std::endl;

        std::string receivedData;
        std::string httpResponse;
        std::cout << port << std::endl;

        if (port == HTTPS_Port) {
            SSL_Connection sslConn("/etc/letsencrypt/live/nicolasbachmaier.com/fullchain.pem",
                                   "/etc/letsencrypt/live/nicolasbachmaier.com/privkey.pem");
            sslConn.accept(new_socket);
            std::vector<char> buffer(BUFFER_SIZE);
            receivedData = sslConn.read();
            if (receivedData == "") {
                std::cout << "Empty Data" << std::endl;
                close(new_socket);
                continue;
            }
            std::string processedData;
            processedData.reserve(receivedData.size());

            for (char c: receivedData) {
                if (c != '\r') {
                    processedData.push_back(c);
                }
            }
            Request request = Request::parse_request(processedData);
            std::cout << "Received Data: " << processedData << std::endl;

            httpResponse = Response::response_builder(request);
            sslConn.write(httpResponse);
        } else {
            std::vector<char> buffer(BUFFER_SIZE);
            int bytesReceived = recv(new_socket, &buffer[0], buffer.size() - 1, 0);

            if (bytesReceived <= 0) {
                if (bytesReceived == 0) {
                    std::cout << "The client has closed the connection." << std::endl;
                } else {
                    std::cerr << "Failed to receive data from client" << std::endl;
                }
                close(new_socket);
                continue;
            }

            buffer[bytesReceived] = '\0';

            std::cout << "Data length is " << bytesReceived << std::endl;

            receivedData = &buffer[0];
            std::string processedData;
            processedData.reserve(receivedData.size());

            for (char c: receivedData) {
                if (c != '\r') {
                    processedData.push_back(c);
                }
            } // Macbook Terminal can't handle the \r
            Request request;
            request = Request::parse_request(processedData);
            std::cout << "Received Data: " << processedData << std::endl;

            std::cout << std::endl;

            httpResponse = Response::response_builder(request);

            send(new_socket, httpResponse.c_str(), httpResponse.length(), 0);
        }
        // Close the socket after handling it
        close(new_socket);
    }
    close(server_fd.at(port));
}