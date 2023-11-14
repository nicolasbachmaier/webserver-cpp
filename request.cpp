#include "headers.h"

Request Request::parse_request(std::string request_content) {
    int pointer = 0; //points to the parsed position
    Request request;

    // Get the Method
    std::string method_input;
    for (pointer; pointer < request_content.length(); pointer++) {
        if (request_content[pointer] == ' ')
            break;
        method_input += request_content[pointer];
    }
    // Set_Method via Map to later implement a control mechanism
    std::unordered_map<std::string, std::function<void()>> method_map;
    method_map["GET"] = [&request]() {
        request.method = "GET";
    };
    method_map["POST"] = [&request]() {
        request.method = "POST";
    };
    method_map["PUT"] = [&request]() {
        request.method = "PUT";
    };
    method_map["DELETE"] = [&request]() {
        request.method = "DELETE";
    };
    method_map["HEAD"] = [&request]() {
        request.method = "HEAD";
    };
    method_map["OPTIONS"] = [&request]() {
        request.method = "OPTIONS";
    };
    method_map["CONNECT"] = [&request]() {
        request.method = "CONNECT";
    };
    method_map["TRACE"] = [&request]() {
        request.method = "TRACE";
    };

    if (method_map.count(method_input) > 0) {
        method_map[method_input]();
    } else {
        method_map["GET"]();
    }


    // Get the requested Location
    std::string location_input;
    for (pointer++; pointer < request_content.length(); pointer++) {
        if (request_content[pointer] == ' ')
            break;
        location_input += request_content[pointer];
    }
    request.location = location_input;

    std::string other_headers;
    int body_breakpoint;
    for (pointer++; pointer < request_content.length(); pointer++) {
        if (request_content[pointer] == '\n')
            body_breakpoint++;
        else
            body_breakpoint = 0;

        if (body_breakpoint > 1)
            break;

        other_headers += request_content[pointer];
    }

    request.populate_header_request(Utils::parse_request(other_headers));

    std::cout << "Method: " << request.method << std::endl;
    std::cout << "Location: " << request.location << std::endl;
    std::cout << "Host: " << request.host << std::endl;
    std::cout << "Sec-Fetch-Site: " << request.sec_fetch_site << std::endl;
    std::cout << "Connection: " << request.connection << std::endl;
    std::cout << "Upgrade Insecure Requests: " << request.upgrade_insecure_requests << std::endl;
    std::cout << "Sec-Fetch-Mode: " << request.sec_fetch_mode << std::endl;
    std::cout << "Accept: " << request.accept << std::endl;
    std::cout << "User Agent: " << request.user_agent << std::endl;
    std::cout << "Accept Language: " << request.accept_language << std::endl;
    std::cout << "Sec-Fetch-Dest: " << request.sec_fetch_dest << std::endl;
    std::cout << "Accept Encoding: " << request.accept_encoding << std::endl;
    std::cout << std::endl;

    return request;
}

void Request::populate_header_request(const std::unordered_map<std::string, std::string> &values) {
    auto it = values.find("Host");
    host = (it != values.end()) ? it->second : "Null";

    it = values.find("Sec-Fetch-Site");
    sec_fetch_site = (it != values.end()) ? it->second : "Null";

    it = values.find("Connection");
    connection = (it != values.end()) ? it->second : "Null";

    it = values.find("Upgrade-Insecure-Requests");
    upgrade_insecure_requests = (it != values.end()) ? std::stoi(it->second) : 0;

    it = values.find("Sec-Fetch-Mode");
    sec_fetch_mode = (it != values.end()) ? it->second : "Null";

    it = values.find("Accept");
    accept = (it != values.end()) ? it->second : "Null";

    it = values.find("User-Agent");
    user_agent = (it != values.end()) ? it->second : "Null";

    it = values.find("Accept-Language");
    accept_language = (it != values.end()) ? it->second : "Null";

    it = values.find("Sec-Fetch-Dest");
    sec_fetch_dest = (it != values.end()) ? it->second : "Null";

    it = values.find("Accept-Encoding");
    accept_encoding = (it != values.end()) ? it->second : "Null";
}
