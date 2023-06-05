#pragma once

#include <string>   // std::string
#include <cstdint>  // std::uint32_t, std::uint16_t
#include <vector>   // std::vector

namespace se {

class ConfigurationReader {
public:
    virtual ~ConfigurationReader() = default;

    virtual const std::vector<std::string>& getUrls() const = 0;
    virtual std::string& crawlMode() = 0;
    virtual std::uint16_t depth() const = 0;
    virtual std::uint32_t maxPages() const = 0;
	virtual std::uint32_t totalSearchList() const = 0;
};

} // namespace se
