#include "headers.h"

const int BUFFER_SIZE = 1024;

int main() {
    Webserver webserver; // Create custom Webserver

    // File Descriptor for the Server Socket (IPv4 Protocol + TCP)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    // Options at Socket Level
#ifdef __APPLE__
    // Set only SO_REUSEADDR
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt Error");
        std::cerr << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt Error");
        std::cerr << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif


    struct sockaddr_in address;
    address.sin_family = AF_INET; // Address Family: IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Bind Socket to all available IP Interfaces
    address.sin_port = htons(webserver.HTTP_Port); // Set the Port - htons makes sure about the network byte order

    // Bind options to the Socket
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address))) {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) { // Mark socket as passive + max. queue length for pending connections
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    int addrlen = sizeof(address);
    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
        // Starts a new socket with the first connection request from the queue.
        if (new_socket < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(address.sin_addr), client_ip, INET_ADDRSTRLEN);
        std::cout << "New connection from " << client_ip << std::endl;

        std::vector<char> buffer(BUFFER_SIZE);
        int bytesReceived = recv(new_socket, &buffer[0], buffer.size() - 1, 0);

        if (bytesReceived <= 0) {
            if (bytesReceived == 0) {
                std::cout << "The client has closed the connection." << std::endl;
            } else {
                std::cerr << "Failed to receive data from client" << std::endl;
            }
            continue;
        }

        buffer[bytesReceived] = '\0';

        std::cout << "Data length is " << bytesReceived << std::endl;

        std::string receivedData(&buffer[0]);
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

        std::string httpResponse = Response::response_builder(request);

        send(new_socket, httpResponse.c_str(), httpResponse.length(), 0);
        // Close the socket after handling it
        close(new_socket);
    }
    close(server_fd);
}
