//
// Created by Nicolas Bachmaier on 13.11.23.
//

#include "webserver.h"
#include <fstream>
#include <iostream>
#include "utils.h"


const std::string Webserver::name = "Bachmaier Technology";
const int Webserver::HTTP_Port = 80;
const int Webserver::HTTPS_Port = 443;

std::string Webserver::response_builder(const Request& request) {
    Custom_File custom_file = Webserver::get_content(request.location);

    return  HttpCodes::HTTP_OK+"\r\n"+
            custom_file.type+"\r\n" +
            "Content-Length: " + std::to_string(custom_file.length) +"\r\n" +
            "Server: " + Webserver::name + "\r\n" +
            "\r\n" + // Double Line Break before Body
            custom_file.content;
}

Custom_File Webserver::get_content(std::string file_name) {
    file_name = Utils::URL_Decode(file_name);
    if(file_name == "/")
        file_name = "index.html";
    if(file_name[0] == '/')
        file_name.erase(0, 1);
    if(file_name[file_name.length()-1] == '/')
        file_name += "index.html";
    if(file_name.find('.') == std::string::npos)
        file_name += ".html";

    std::ifstream file("html/"+file_name);
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

Request Webserver::parse_request(std::string request_content) {
    int pointer = 0; //points to the parsed position
    Request request;

    // Get the Method
    std::string method_input;
    for (pointer; pointer < request_content.length(); pointer++) {
        if(request_content[pointer] == ' ')
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
        if(request_content[pointer] == ' ')
            break;
        location_input += request_content[pointer];
    }
    request.location = location_input;



    std::cout << "Method: " << request.method << std::endl;
    std::cout << "Location: " << request.location << std::endl;
    std::cout << std::endl;

    return request;
}