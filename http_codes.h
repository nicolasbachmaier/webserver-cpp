#pragma once

#include <string>

class HttpCodes {
public:
    static const std::string HTTP_CONTINUE;
    static const std::string HTTP_SWITCHING_PROTOCOLS;
    static const std::string HTTP_OK;
    static const std::string HTTP_CREATED;
    static const std::string HTTP_ACCEPTED;
    static const std::string HTTP_NON_AUTHORITATIVE_INFORMATION;
    static const std::string HTTP_NO_CONTENT;
    static const std::string HTTP_RESET_CONTENT;
    static const std::string HTTP_PARTIAL_CONTENT;
    static const std::string HTTP_MULTIPLE_CHOICES;
    static const std::string HTTP_MOVED_PERMANENTLY;
    static const std::string HTTP_FOUND;
    static const std::string HTTP_SEE_OTHER;
    static const std::string HTTP_NOT_MODIFIED;
    static const std::string HTTP_USE_PROXY;
    static const std::string HTTP_TEMPORARY_REDIRECT;
    static const std::string HTTP_BAD_REQUEST;
    static const std::string HTTP_UNAUTHORIZED;
    static const std::string HTTP_PAYMENT_REQUIRED;
    static const std::string HTTP_FORBIDDEN;
    static const std::string HTTP_NOT_FOUND;
    static const std::string HTTP_METHOD_NOT_ALLOWED;
    static const std::string HTTP_NOT_ACCEPTABLE;
    static const std::string HTTP_PROXY_AUTHENTICATION_REQUIRED;
    static const std::string HTTP_REQUEST_TIMEOUT;
    static const std::string HTTP_CONFLICT;
    static const std::string HTTP_GONE;
    static const std::string HTTP_LENGTH_REQUIRED;
    static const std::string HTTP_PRECONDITION_FAILED;
    static const std::string HTTP_REQUEST_ENTITY_TOO_LARGE;
    static const std::string HTTP_REQUEST_URI_TOO_LONG;
    static const std::string HTTP_UNSUPPORTED_MEDIA_TYPE;
    static const std::string HTTP_REQUESTED_RANGE_NOT_SATISFIABLE;
    static const std::string HTTP_EXPECTATION_FAILED;
    static const std::string HTTP_INTERNAL_SERVER_ERROR;
    static const std::string HTTP_NOT_IMPLEMENTED;
    static const std::string HTTP_BAD_GATEWAY;
    static const std::string HTTP_SERVICE_UNAVAILABLE;
    static const std::string HTTP_GATEWAY_TIMEOUT;
    static const std::string HTTP_HTTP_VERSION_NOT_SUPPORTED;
};