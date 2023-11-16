#include "headers.h"

std::unordered_map<std::string, Custom_File> Custom_File_Handler::file_object;
std::mutex Custom_File_Handler::fileObjectMutex;

void Custom_File_Handler::create_file(const std::string &file_name, std::filesystem::path &file_path) {

    Custom_File custom_file;

    // Last Modified Time
    auto ftime = std::filesystem::last_write_time(file_path);
    auto sys_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    std::time_t cftime = std::chrono::system_clock::to_time_t(sys_time);
    tm *gmt_tm = gmtime(&cftime);
    char date_buffer[80];
    strftime(date_buffer, sizeof(date_buffer), "%a, %d %b %Y %H:%M:%S GMT", gmt_tm);
    std::string formatted_last_modified_date(date_buffer);

    std::ifstream file(file_path);
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
    file_object.insert(std::make_pair(file_name, custom_file));
}

Response Custom_File_Handler::get_file(const std::string &file_name) {
    std::lock_guard<std::mutex> guard(fileObjectMutex);
    std::string html_path = "html/";
    std::filesystem::path file_path(html_path + file_name);

    Custom_File custom_file;

    if (std::filesystem::exists(file_path)) {
        if (file_object.find(file_name) == file_object.end()) {
            create_file(file_name, file_path); // Load file into memory if it doesn't already exist
            std::cout << "Created: " << file_name << std::endl;
        } else {
            std::cout << "Loaded: " << file_name << std::endl;
        }
        custom_file = file_object.at(file_name);
        custom_file.last_access = std::chrono::steady_clock::now();
        file_object.at(file_name) = custom_file;
    }
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

void Custom_File_Handler::delete_file() {
    const int EXPIRATION_MINUTES = 5;
    auto now = std::chrono::steady_clock::now();

    for (auto it = file_object.begin(); it != file_object.end();) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.last_access);
        if (elapsed.count() >= EXPIRATION_MINUTES) {
            it = file_object.erase(it);
        } else {
            ++it;
        }
    }
}

void Custom_File_Handler::file_monitor() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::minutes(1)); // Run every minute
        print_all_file_names();
        delete_file();
    }
}


void Custom_File_Handler::print_all_file_names() {
    std::lock_guard<std::mutex> guard(fileObjectMutex); // Ensure thread safety

    for (const auto &pair: file_object) {
        const Custom_File &file = pair.second;
        std::cout << "File Name: " << file.name << std::endl;
    }
}