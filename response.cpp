#include "headers.h"

std::string Response::response_builder(const Request &request) {
    Response response = Response::get_content(request.location);

    return HttpCodes::HTTP_OK + "\r\n" +
           response.content_type + "\r\n" +
           "Content-Length: " + std::to_string(response.content_length) + "\r\n" +
           "Server: " + Webserver::server + "\r\n" +
           "Strict-Transport-Security: " + Webserver::strict_transport_security + "\r\n" +
           "X-Content-Type-Options: " + Webserver::x_content_type_options + "\r\n" +
           "X-Frame-Options: " + Webserver::x_frame_options + "\r\n" +
           "Content-Security-Policy: " + Webserver::content_security_policy + "\r\n" +
           "X-XSS-Protection: " + Webserver::x_xss_protection + "\r\n" +
           "Access-Control-Allow-Origin: " + Webserver::access_control_allow_origin + "\r\n" +
           "Access-Control-Allow-Credentials: " + Webserver::access_control_allow_credentials + "\r\n" +
           "Access-Control-Expose-Headers: " + Webserver::access_control_expose_headers + "\r\n" +
           "\r\n" + // Double Line Break before Body
           response.body;
}

Response Response::get_content(std::string file_name) {
    file_name = Utils::URL_Decode(file_name);
    if (file_name == "/")
        file_name = "index.html";
    if (file_name[0] == '/')
        file_name.erase(0, 1);
    if (file_name[file_name.length() - 1] == '/')
        file_name += "index.html";
    if (file_name.find('.') == std::string::npos)
        file_name += ".html";

    std::ifstream file("html/" + file_name);
    std::string content;
    char ch;

    while (file.get(ch)) {
        content += ch;
    }
    file.close();


    Response response;
    response.content_type = ContentType::get_content_type(file_name);
    response.body = content;
    response.content_length = content.length();
    return response;
}