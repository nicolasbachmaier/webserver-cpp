#pragma once

#include "headers.h"
#include "request.h"

class Response {
public:
    std::string status;
    std::string date;
    std::string last_modified;
    std::string etag;
    static std::string accept_ranges;
    unsigned long content_length;
    std::string content_type;
    static std::string connection;
    std::string body;

    static std::string response_builder(const Request &request);

    static Response get_content(std::string host, std::string file_name);
};