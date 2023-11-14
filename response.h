#pragma once

#include "headers.h"
#include "request.h"

class Response {
public:
    std::string status;
    std::string date;
    std::string last_modified;
    std::string etag;
    std::string accept_ranges;
    unsigned long content_length;
    std::string content_type;
    std::string connection;
    std::string body;

    static std::string response_builder(const Request &request);

    static Response get_content(std::string file_name = "index.html");
};