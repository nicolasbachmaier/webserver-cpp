#include "http_codes.h"

const std::string HttpCodes::HTTP_CONTINUE = "HTTP/1.1 100 Continue";
const std::string HttpCodes::HTTP_SWITCHING_PROTOCOLS = "HTTP/1.1 101 Switching Protocols";
const std::string HttpCodes::HTTP_OK = "HTTP/1.1 200 OK";
const std::string HttpCodes::HTTP_CREATED = "HTTP/1.1 201 Created";
const std::string HttpCodes::HTTP_ACCEPTED = "HTTP/1.1 202 Accepted";
const std::string HttpCodes::HTTP_NON_AUTHORITATIVE_INFORMATION = "HTTP/1.1 203 Non-Authoritative Information";
const std::string HttpCodes::HTTP_NO_CONTENT = "HTTP/1.1 204 No Content";
const std::string HttpCodes::HTTP_RESET_CONTENT = "HTTP/1.1 205 Reset Content";
const std::string HttpCodes::HTTP_PARTIAL_CONTENT = "HTTP/1.1 206 Partial Content";
const std::string HttpCodes::HTTP_MULTIPLE_CHOICES = "HTTP/1.1 300 Multiple Choices";
const std::string HttpCodes::HTTP_MOVED_PERMANENTLY = "HTTP/1.1 301 Moved Permanently";
const std::string HttpCodes::HTTP_FOUND = "HTTP/1.1 302 Found";
const std::string HttpCodes::HTTP_SEE_OTHER = "HTTP/1.1 303 See Other";
const std::string HttpCodes::HTTP_NOT_MODIFIED = "HTTP/1.1 304 Not Modified";
const std::string HttpCodes::HTTP_USE_PROXY = "HTTP/1.1 305 Use Proxy";
const std::string HttpCodes::HTTP_TEMPORARY_REDIRECT = "HTTP/1.1 307 Temporary Redirect";
const std::string HttpCodes::HTTP_BAD_REQUEST = "HTTP/1.1 400 Bad Request";
const std::string HttpCodes::HTTP_UNAUTHORIZED = "HTTP/1.1 401 Unauthorized";
const std::string HttpCodes::HTTP_PAYMENT_REQUIRED = "HTTP/1.1 402 Payment Required";
const std::string HttpCodes::HTTP_FORBIDDEN = "HTTP/1.1 403 Forbidden";
const std::string HttpCodes::HTTP_NOT_FOUND = "HTTP/1.1 404 Not Found";
const std::string HttpCodes::HTTP_METHOD_NOT_ALLOWED = "HTTP/1.1 405 Method Not Allowed";
const std::string HttpCodes::HTTP_NOT_ACCEPTABLE = "HTTP/1.1 406 Not Acceptable";
const std::string HttpCodes::HTTP_PROXY_AUTHENTICATION_REQUIRED = "HTTP/1.1 407 Proxy Authentication Required";
const std::string HttpCodes::HTTP_REQUEST_TIMEOUT = "HTTP/1.1 408 Request Timeout";
const std::string HttpCodes::HTTP_CONFLICT = "HTTP/1.1 409 Conflict";
const std::string HttpCodes::HTTP_GONE = "HTTP/1.1 410 Gone";
const std::string HttpCodes::HTTP_LENGTH_REQUIRED = "HTTP/1.1 411 Length Required";
const std::string HttpCodes::HTTP_PRECONDITION_FAILED = "HTTP/1.1 412 Precondition Failed";
const std::string HttpCodes::HTTP_REQUEST_ENTITY_TOO_LARGE = "HTTP/1.1 413 Request Entity Too Large";
const std::string HttpCodes::HTTP_REQUEST_URI_TOO_LONG = "HTTP/1.1 414 Request-URI Too Long";
const std::string HttpCodes::HTTP_UNSUPPORTED_MEDIA_TYPE = "HTTP/1.1 415 Unsupported Media Type";
const std::string HttpCodes::HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = "HTTP/1.1 416 Requested Range Not Satisfiable";
const std::string HttpCodes::HTTP_EXPECTATION_FAILED = "HTTP/1.1 417 Expectation Failed";
const std::string HttpCodes::HTTP_INTERNAL_SERVER_ERROR = "HTTP/1.1 500 Internal Server Error";
const std::string HttpCodes::HTTP_NOT_IMPLEMENTED = "HTTP/1.1 501 Not Implemented";
const std::string HttpCodes::HTTP_BAD_GATEWAY = "HTTP/1.1 502 Bad Gateway";
const std::string HttpCodes::HTTP_SERVICE_UNAVAILABLE = "HTTP/1.1 503 Service Unavailable";
const std::string HttpCodes::HTTP_GATEWAY_TIMEOUT = "HTTP/1.1 504 Gateway Timeout";
const std::string HttpCodes::HTTP_HTTP_VERSION_NOT_SUPPORTED = "HTTP/1.1 505 HTTP Version Not Supported";