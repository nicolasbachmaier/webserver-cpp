#pragma once
#include "headers.h"

class Request {
public:
    std::string method;
    std::string location;
    std::string host;
    std::string sec_fetch_site;
    std::string connection;
    int upgrade_insecure_requests;
    std::string sec_fetch_mode;
    std::string accept;
    std::string user_agent;
    std::string accept_language;
    std::string sec_fetch_dest;
    std::string accept_encoding;

    void populate_header_request(const std::unordered_map<std::string, std::string> &values);
    static Request parse_request(std::string request_content);
};
