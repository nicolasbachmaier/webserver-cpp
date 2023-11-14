cmake_minimum_required(VERSION 3.26)
project(Webserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(Webserver main.cpp
        http_codes.h
        content_type.h
        webserver.cpp
        webserver.h
        http_codes.cpp
        content_type.cpp
        file_handler.cpp
        file_handler.h
        utils.cpp
        utils.h
        request.cpp
        request.h
        headers.h
        response.cpp
        response.h)
