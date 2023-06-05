#pragma once

#include <string>   // std::string
#include <sstream>  // std::stringstream

namespace se {

class Downloader {
public:
    virtual ~Downloader() = default;

    virtual std::ostringstream downloadPage(const std::string& a_url) = 0;
};

} // namespace se
