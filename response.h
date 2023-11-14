#pragma once

#include "Webserver.h"
#include "headers.h"

class Response : public Webserver {
public:
    std::string status;
    std::string date;
    std::string last_modified;
    std::string etag;
    std::string accept_ranges;
    std::string content_length;
    std::string content_type;
    std::string connection;
    std::string body;

    static void response_builder(const Request &request);
};