#include "headers.h"


int main() {
    std::thread http_server(Webserver::start_webserver, Webserver::HTTP_Port);
    std::thread https_server(Webserver::start_webserver, Webserver::HTTPS_Port);
    std::thread file_monitor(Custom_File_Handler::file_monitor);

    if (http_server.joinable())
        http_server.join();
    if (https_server.joinable())
        https_server.join();
    file_monitor.detach();
}
