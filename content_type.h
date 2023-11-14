#pragma once

#include <string>

class ContentType {
public:
    static const std::string TEXT_PLAIN;
    static const std::string TEXT_HTML;
    static const std::string TEXT_CSS;
    static const std::string TEXT_CSV;
    static const std::string TEXT_XML;

    static const std::string IMAGE_GIF;
    static const std::string IMAGE_JPEG;
    static const std::string IMAGE_PNG;
    static const std::string IMAGE_SVG;
    static const std::string IMAGE_WEBP;

    static const std::string AUDIO_MPEG;
    static const std::string AUDIO_WAV;
    static const std::string AUDIO_WEBA;

    static const std::string VIDEO_MP4;
    static const std::string VIDEO_WEBM;
    static const std::string VIDEO_OGG;

    static const std::string APPLICATION_JSON;
    static const std::string APPLICATION_XML;
    static const std::string APPLICATION_ZIP;
    static const std::string APPLICATION_PDF;
    static const std::string APPLICATION_SQL;
    static const std::string APPLICATION_GRAPHQL;

    static std::string get_content_type(const std::string& file_name);
};
