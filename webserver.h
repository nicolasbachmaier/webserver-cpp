#pragma once

#include <string>
#include <utility>
#include "http_codes.h"
#include "content_type.h"
#include "file_handler.h"

class Request {
public:
    std::string method;
    std::string location;
};

class Webserver {
public:
    static const std::string name;
    static const int HTTP_Port;
    static const int HTTPS_Port;

    static std::string response_builder(const Request& request);
    static Custom_File get_content(std::string file_name="index.html");
    static Request parse_request(std::string request_content);
};