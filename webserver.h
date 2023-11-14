#pragma once
#include "headers.h"
class Webserver {
public:
    static const std::string name;
    static const int HTTP_Port;
    static const int HTTPS_Port;

    static std::string response_builder(const Request& request);
    static Custom_File get_content(std::string file_name="index.html");
};