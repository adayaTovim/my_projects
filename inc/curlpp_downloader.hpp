#pragma once

#include <sstream>              // std::stringstream
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp> // Curlpp headers

#include "downloader.hpp" // Inheritance header

namespace se {

class CurlppDownloader : public Downloader {
public:
    CurlppDownloader();
    CurlppDownloader(const CurlppDownloader& a_other) = delete;
    CurlppDownloader& operator=(const CurlppDownloader& a_other) = delete;
    ~CurlppDownloader() = default;

    std::ostringstream downloadPage(const std::string& a_url) override;

private:
    curlpp::Easy m_requester;
};

} // namespace se
