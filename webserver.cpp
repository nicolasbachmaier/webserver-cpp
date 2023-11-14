#include "headers.h"

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

