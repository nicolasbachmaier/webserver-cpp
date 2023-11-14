#pragma once
#include "headers.h"

class Utils {
public:
    static std::string URL_Decode (const std::string &URL);
    static std::unordered_map<std::string, std::string> parse_request (const std::string &str);
};