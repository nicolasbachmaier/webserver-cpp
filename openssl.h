#pragma once

#include "headers.h"

class SSL_Connection {
private:
    SSL_CTX *ctx;
    SSL *ssl;
    int handshake_status;

    void initialize_ssl_context();

    void configure_context(const std::string &cert_file, const std::string &key_file);

    // Function to handle non-blocking mode waiting
    static bool wait_for_socket(int socket, int mode);

public:
    SSL_Connection(const std::string &cert_file, const std::string &key_file) : ctx(nullptr), ssl(nullptr),
                                                                                handshake_status(0) {
        initialize_ssl_context();
        configure_context(cert_file, key_file);
    }

    ~SSL_Connection() {
        if (ssl) {
            SSL_shutdown(ssl);
            SSL_free(ssl);
        }
        if (ctx) {
            SSL_CTX_free(ctx);
            EVP_cleanup();
        }
    }

    bool accept(int client_socket);

    std::string read();

    void write(const std::string &msg);
};
