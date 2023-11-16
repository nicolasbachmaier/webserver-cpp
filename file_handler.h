#pragma once

#include "headers.h"
#include "response.h"

struct Custom_File {
    unsigned long length;
    std::string name;
    std::string content;
    std::string last_modified_date;
    std::chrono::time_point<std::chrono::steady_clock> last_access;
};

class Custom_File_Handler {
private:
    static std::mutex fileObjectMutex;

    static void create_file(const std::string &file_name, std::filesystem::path &file_path);

    static void delete_file();

public:
    static std::unordered_map<std::string, Custom_File> file_object;

    static void file_monitor();

    static Response get_file(const std::string &file_name);

    static void print_all_file_names();
};