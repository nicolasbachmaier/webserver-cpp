#include "headers.h"

std::string Utils::URL_Decode(const std::string &URL) {
    std::string decodedURL;
    for (std::size_t i = 0; i < URL.length(); ++i) {
        if (URL[i] == '%') {
            int value;
            std::istringstream is(URL.substr(i + 1, 2));
            if (is >> std::hex >> value) {
                decodedURL += static_cast<char>(value);
                i += 2;
            } else {
                return {}; // invalid URL
            }
        } else if (URL[i] == '+') {
            decodedURL += ' ';
        } else {
            decodedURL += URL[i];
        }
    }
    return decodedURL;
}

std::unordered_map<std::string, std::string> Utils::parse_request (const std::string &str) {
    std::unordered_map<std::string, std::string> values;
    std::istringstream iss(str);
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string key, value;
        if (std::getline(lineStream, key, ':') && std::getline(lineStream, value)) {
            // Trim leading and trailing whitespace from value
            value.erase(0, value.find_first_not_of(' '));
            value.erase(value.find_last_not_of(' ') + 1);
            values[key] = value;
        }
    }
    return values;
}