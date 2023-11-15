#pragma once

#include "headers.h"
#include "request.h"

class Webserver {
private:
    static const int BUFFER_SIZE = 1024;

    static std::unordered_map<int, int> server_fd;
    static std::unordered_map<int, struct sockaddr_in> address;
    static std::unordered_map<int, int> addrlen;

    static void initialize_socket(const int &port);

public:
    static const int HTTP_Port;
    static const int HTTPS_Port;
    static const std::string server;
    static const std::string strict_transport_security;
    static const std::string x_content_type_options;
    static const std::string x_frame_options;
    static const std::string content_security_policy;
    static const std::string x_xss_protection;
    static const std::string access_control_allow_origin;
    static const std::string access_control_allow_credentials;
    static const std::string access_control_expose_headers;

    static void start_webserver(const int &port);

};