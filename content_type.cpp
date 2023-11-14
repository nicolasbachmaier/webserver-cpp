#include "headers.h"

const std::string ContentType::TEXT_PLAIN = "Content-Type: text/plain";
const std::string ContentType::TEXT_HTML = "Content-Type: text/html";
const std::string ContentType::TEXT_CSS = "Content-Type: text/css";
const std::string ContentType::TEXT_CSV = "Content-Type: text/csv";
const std::string ContentType::TEXT_XML = "Content-Type: text/xml";

const std::string ContentType::IMAGE_GIF = "Content-Type: image/gif";
const std::string ContentType::IMAGE_JPEG = "Content-Type: image/jpeg";
const std::string ContentType::IMAGE_PNG = "Content-Type: image/png";
const std::string ContentType::IMAGE_SVG = "Content-Type: image/svg+xml";
const std::string ContentType::IMAGE_WEBP = "Content-Type: image/webp";

const std::string ContentType::AUDIO_MPEG = "Content-Type: audio/mpeg";
const std::string ContentType::AUDIO_WAV = "Content-Type: audio/wav";
const std::string ContentType::AUDIO_WEBA = "Content-Type: audio/webm";

const std::string ContentType::VIDEO_MP4 = "Content-Type: video/mp4";
const std::string ContentType::VIDEO_WEBM = "Content-Type: video/webm";
const std::string ContentType::VIDEO_OGG = "Content-Type: video/ogg";

const std::string ContentType::APPLICATION_JSON = "Content-Type: application/json";
const std::string ContentType::APPLICATION_XML = "Content-Type: application/xml";
const std::string ContentType::APPLICATION_ZIP = "Content-Type: application/zip";
const std::string ContentType::APPLICATION_PDF = "Content-Type: application/pdf";
const std::string ContentType::APPLICATION_SQL = "Content-Type: application/sql";
const std::string ContentType::APPLICATION_GRAPHQL = "Content-Type: application/graphql";

std::string ContentType::get_content_type(const std::string& file_name) {
    size_t pos = file_name.find_last_of(".");
    std::string extension;
    if (pos != std::string::npos) {
        extension = file_name.substr(pos+1);
    } else {
        return TEXT_PLAIN;
    }

    if(extension == "html") {
        return TEXT_HTML;
    }
    if(extension == "css") {
        return TEXT_CSS;
    }
    if(extension == "csv") {
        return TEXT_CSV;
    }
    if(extension == "xml") {
        return TEXT_XML;
    }
    if(extension == "gif") {
        return IMAGE_GIF;
    }
    if(extension == "jpeg" || extension == "jpg") {
        return IMAGE_JPEG;
    }
    if(extension == "png") {
        return IMAGE_PNG;
    }
    if(extension == "svg") {
        return IMAGE_SVG;
    }
    if(extension == "webp") {
        return IMAGE_WEBP;
    }
    if(extension == "mp3") {
        return AUDIO_MPEG;
    }
    if(extension == "wav") {
        return AUDIO_WAV;
    }
    if(extension == "weba") {
        return AUDIO_WEBA;
    }
    if(extension == "mp4") {
        return VIDEO_MP4;
    }
    if(extension == "webm") {
        return VIDEO_WEBM;
    }
    if(extension == "ogg") {
        return VIDEO_OGG;
    }
    if(extension == "json") {
        return APPLICATION_JSON;
    }
    if(extension == "xml") {
        return APPLICATION_XML;
    }
    if(extension == "zip") {
        return APPLICATION_ZIP;
    }
    if(extension == "pdf") {
        return APPLICATION_PDF;
    }
    if(extension == "sql") {
        return APPLICATION_SQL;
    }
    if(extension == "graphql") {
        return APPLICATION_GRAPHQL;
    }
    // If no matching extension found, return plain text
    return TEXT_PLAIN;
}