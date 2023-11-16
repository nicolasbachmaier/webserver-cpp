#include "headers.h"

void Custom_File_Handler::create_file(const std::string &file_name) {
    std::string html_path = "html/";
    std::filesystem::path file_path(html_path + file_name);

    Custom_File custom_file;

    if (std::filesystem::exists(file_path)) {
        // Last Modified Time
        auto ftime = std::filesystem::last_write_time(file_path);
        auto sys_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        std::time_t cftime = std::chrono::system_clock::to_time_t(sys_time);
        tm *gmt_tm = gmtime(&cftime);
        char date_buffer[80];
        strftime(date_buffer, sizeof(date_buffer), "%a, %d %b %Y %H:%M:%S GMT", gmt_tm);
        std::string formatted_last_modified_date(date_buffer);

        std::ifstream file(html_path + file_name);
        std::string content;
        char ch;

        while (file.get(ch)) {
            content += ch;
        }
        file.close();
        custom_file.name = file_name;
        custom_file.content = content;
        custom_file.length = content.length();
        custom_file.last_modified_date = formatted_last_modified_date;
    } else {
        // 404 File not Found
    }
    file_object.insert(std::make_pair(file_name, custom_file));
}

Response Custom_File_Handler::get_file(const std::string &file_name) {
    Custom_File custom_file;
    if (file_object.find(file_name) == file_object.end()) {
        create_file(file_name); // Load file into memory if it doesn't already exist
    }
    custom_file = file_object.at(file_name);
    // Get the current time
    time_t time_now = time(0);
    tm *gmt_tm = gmtime(&time_now);
    char current_date_buffer[80];
    strftime(current_date_buffer, sizeof(current_date_buffer), "%a, %d %b %Y %H:%M:%S GMT", gmt_tm);
    std::string current_date(current_date_buffer);

    Response response;
    response.content_type = ContentType::get_content_type(file_name);
    response.body = custom_file.content;
    response.content_length = custom_file.length;
    response.date = current_date;
    response.last_modified = custom_file.last_modified_date;
    return response;
}
