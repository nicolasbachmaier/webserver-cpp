cmake_minimum_required(VERSION 3.25)
project(Webserver)

set(CMAKE_CXX_STANDARD 17)

# Find the OpenSSL package
# Set paths based on architecture
if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@3)
elseif (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
endif ()
find_package(OpenSSL REQUIRED)

if (OPENSSL_FOUND)
    message(STATUS "OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL libraries: ${OPENSSL_LIBRARIES}")
    include_directories(${OPENSSL_INCLUDE_DIR})
    link_libraries(${OPENSSL_LIBRARIES})
endif ()


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
        response.h
        openssl.cpp
        openssl.h)
