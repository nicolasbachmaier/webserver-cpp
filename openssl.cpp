#include "headers.h"

void SSL_Connection::initialize_ssl_context() {
    OpenSSL_add_ssl_algorithms();
    SSL_load_error_strings();
    ERR_load_crypto_strings();
    const SSL_METHOD *method = TLS_server_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    SSL_CTX_set_ecdh_auto(ctx, 1);
    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);
    SSL_CTX_set_max_proto_version(ctx, TLS1_3_VERSION);
}

void SSL_Connection::configure_context(const std::string &cert_file, const std::string &key_file) {
    while (true) {
        if (SSL_CTX_use_certificate_file(ctx, cert_file.c_str(), SSL_FILETYPE_PEM) <= 0 ||
            SSL_CTX_use_PrivateKey_file(ctx, key_file.c_str(), SSL_FILETYPE_PEM) <= 0) {
            ERR_print_errors_fp(stderr);
            std::cerr << EXIT_FAILURE << std::endl;
        } else {
            break;
        }
    }
}

bool SSL_Connection::wait_for_socket(int socket, int mode) {
    fd_set fds;
    struct timeval tv;

    FD_ZERO(&fds);
    FD_SET(socket, &fds);

    tv.tv_sec = 10; // Set a timeout (10 seconds)
    tv.tv_usec = 0;

    if (mode == SSL_ERROR_WANT_READ) {
        return select(socket + 1, &fds, NULL, NULL, &tv) == 1;
    } else if (mode == SSL_ERROR_WANT_WRITE) {
        return select(socket + 1, NULL, &fds, NULL, &tv) == 1;
    }
    return false;
}


bool SSL_Connection::accept(int client_socket) {
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        ssl = nullptr;
    }
    std::cout << "SSL points to: " << ssl << std::endl;
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_socket);
    std::cout << "SSL points to: " << ssl << std::endl;
    int accept_result;
    while ((accept_result = SSL_accept(ssl)) <= 0) {
        int ssl_err = SSL_get_error(ssl, accept_result);

        if (ssl_err == SSL_ERROR_WANT_READ || ssl_err == SSL_ERROR_WANT_WRITE) {
            if (!wait_for_socket(client_socket, ssl_err)) {
                std::cout << "Socket not ready for SSL handshake" << std::endl;
                SSL_shutdown(ssl);
                SSL_free(ssl);
                ssl = nullptr;
                close(client_socket);
                return false;
            }
        } else {
            std::cout << "SSL points to: " << ssl << std::endl;
            std::cout << "Error accepting SSL connection" << std::endl;
            ERR_print_errors_fp(stderr);
            SSL_shutdown(ssl);
            SSL_free(ssl);
            ssl = nullptr;
            close(client_socket);
            return false;
        }
    }

    while (true) {
        handshake_status = SSL_do_handshake(ssl);
        if (handshake_status == 1) {
            std::cout << "SSL handshake successful" << std::endl;
            break;
        } else {
            int err = SSL_get_error(ssl, handshake_status);
            if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) {
                std::cout << "Error performing SSL handshake" << std::endl;
                ERR_print_errors_fp(stderr);
                SSL_shutdown(ssl);
                SSL_free(ssl);
                ssl = nullptr;
                close(client_socket);
                return false;
            }
        }
    }
    return true;
}

std::string SSL_Connection::read() {
    const int read_size = 1024;
    char buffer[read_size];
    std::string data;

    while (ssl) {
        std::cout << "Read SSL points to: " << ssl << std::endl;
        int bytes = SSL_read(ssl, buffer, read_size - 1);
        std::cout << std::endl << std::endl << "Buffer: " << buffer << std::endl;

        if (bytes > 0) {
            buffer[bytes] = '\0';
            data.append(buffer);
            break;
        } else if (bytes == 0) {
            break;
        } else {
            int err = SSL_get_error(ssl, bytes);
            if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE) {
                if (!wait_for_socket(SSL_get_fd(ssl), err)) {
                    std::cerr << "Socket not ready for SSL read" << std::endl;
                    break;
                }
            } else {
                std::cerr << "SSL read error: " << err << std::endl;
                break;
            }
        }
    }
    return data;
}


void SSL_Connection::write(const std::string &msg) {
    size_t totalWritten = 0;
    size_t length = msg.length();

    while (totalWritten < length) {
        int bytes = SSL_write(ssl, msg.c_str() + totalWritten, length - totalWritten);

        if (bytes > 0) {
            totalWritten += bytes;
        } else {
            int err = SSL_get_error(ssl, bytes);
            if (err == SSL_ERROR_WANT_WRITE) {
                if (!wait_for_socket(SSL_get_fd(ssl), err)) {
                    std::cerr << "Socket not ready for SSL write" << std::endl;
                    break;
                }
            } else {
                std::cerr << "SSL write error: " << err << std::endl;
                break;
            }
        }
    }
}
