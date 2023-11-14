#pragma once

#include "headers.h"
#include "request.h"

class Webserver {
public:
    static const std::string server;
    static const std::string strict_transport_security;
    static const std::string x_content_type_options;
    static const std::string x_frame_options;
    static const std::string content_security_policy;
    static const std::string x_xss_protection;
    static const std::string access_control_allow_origin;
    static const std::string access_control_allow_credentials;
    static const std::string access_control_expose_headers;

    static const int HTTP_Port;
    static const int HTTPS_Port;

    static std::string response_builder(const Request &request);

    static Custom_File get_content(std::string file_name = "index.html");
};