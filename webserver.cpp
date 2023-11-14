#include "headers.h"

const std::string Webserver::server = "Bachmaier Technology";
const std::string Webserver::strict_transport_security = "max-age=31536000; includeSubDomains"; // HSTS policy for one year including subdomains
const std::string Webserver::x_content_type_options = "nosniff"; // disable MIME type sniffing
const std::string Webserver::x_frame_options = "SAMEORIGIN"; // allow frame/iframe embedding from same origin only
const std::string Webserver::content_security_policy = "default-src 'self'; script-src 'self' 'unsafe-inline'; style-src 'self' 'unsafe-inline'"; // allow content loading from the same origin only
const std::string Webserver::x_xss_protection = "1; mode=block"; // enable XSS protection and block rendering if an attack is detected
const std::string Webserver::access_control_allow_origin = "*"; // allow any origin (this is a very permissive setting, and you might want to restrict it)
const std::string Webserver::access_control_allow_credentials = "true"; // allows cookies to be sent with CORS requests
const std::string Webserver::access_control_expose_headers = "Content-Length"; // exposes the Content-Length header to CORS requests
const int Webserver::HTTP_Port = 80;
const int Webserver::HTTPS_Port = 443;