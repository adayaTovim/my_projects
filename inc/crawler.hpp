#pragma once

#include <string>   // std::string
#include <cstdint>  // std::uint32_t

#include "web_page.hpp"         // WebPage header
#include "curlpp_downloader.hpp"// CurlppDownloader header
#include "gumbo_parser.hpp"     // GumboParser header
#include "update_data.hpp"      // UpdateData header
#include "iupdate.hpp"          // IUpdate header

namespace se {

class Crawler {
public:
    Crawler(IUpdate& a_updater);
    Crawler(const Crawler& a_other) = delete;
    Crawler& operator=(const Crawler& a_other) = delete;
    ~Crawler() = default;

    WebPage crawlOneUrl(const std::string& a_url);
    uint32_t getFailedLinks() const noexcept;

private:
    CurlppDownloader m_downloader;
    GumboParser m_parser;
    UpdateData m_updater;
    uint32_t m_failedLinks;
};

} // namespace se
