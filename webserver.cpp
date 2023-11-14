#include "headers.h"

const std::string Webserver::server = "Bachmaier Technology";
const std::string Webserver::strict_transport_security = "max-age=31536000; includeSubDomains"; // HSTS policy for one year including subdomains
const std::string Webserver::x_content_type_options = "nosniff"; // disable MIME type sniffing
const std::string Webserver::x_frame_options = "SAMEORIGIN"; // allow frame/iframe embedding from same origin only
const std::string Webserver::content_security_policy = "default-src 'self'"; // allow content loading from the same origin only
const std::string Webserver::x_xss_protection = "1; mode=block"; // enable XSS protection and block rendering if an attack is detected
const std::string Webserver::access_control_allow_origin = "*"; // allow any origin (this is a very permissive setting and you might want to restrict it)
const std::string Webserver::access_control_allow_credentials = "true"; // allows cookies to be sent with CORS requests
const std::string Webserver::access_control_expose_headers = "Content-Length"; // exposes the Content-Length header to CORS requests
const int Webserver::HTTP_Port = 80;
const int Webserver::HTTPS_Port = 443;

std::string Webserver::response_builder(const Request &request) {
    Custom_File custom_file = Webserver::get_content(request.location);

    return HttpCodes::HTTP_OK + "\r\n" +
           custom_file.type + "\r\n" +
           "Content-Length: " + std::to_string(custom_file.length) + "\r\n" +
           "Server: " + Webserver::server + "\r\n" +
           "\r\n" + // Double Line Break before Body
           custom_file.content;
}

Custom_File Webserver::get_content(std::string file_name) {
    file_name = Utils::URL_Decode(file_name);
    if (file_name == "/")
        file_name = "index.html";
    if (file_name[0] == '/')
        file_name.erase(0, 1);
    if (file_name[file_name.length() - 1] == '/')
        file_name += "index.html";
    if (file_name.find('.') == std::string::npos)
        file_name += ".html";

    std::ifstream file("html/" + file_name);
    std::string content;
    char ch;

    while (file.get(ch)) {
        content += ch;
    }
    file.close();


    Custom_File custom_file;
    custom_file.name = file_name;
    custom_file.type = ContentType::get_content_type(custom_file.name);
    custom_file.content = content;
    custom_file.length = content.length();

    return custom_file;
}

