#include "utils.h"

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