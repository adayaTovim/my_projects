#pragma once

#include <string>   // std::string
#include <cstdint>  // std::uint32_t, std::uint16_t
#include <vector>   // std::vector

#include "configuration_reader.hpp" // Inheritance header

namespace se {

class JsonFile : public ConfigurationReader {
public:
    explicit JsonFile(const std::string& a_filename);
    JsonFile(const JsonFile& a_other) = delete;
    JsonFile& operator=(const JsonFile& a_other) = delete;
    ~JsonFile() = default;

    const std::vector<std::string>& getUrls() const override;
    std::string& crawlMode() override;
    std::uint16_t depth() const override;
    std::uint32_t maxPages() const override;
    std::uint32_t totalSearchList() const override;

private:
    std::string m_filename;
    std::vector<std::string> m_urls;
    std::string m_crawlMode;
    std::uint16_t m_depth;
    std::uint32_t m_maxPages;
	std::uint32_t m_totalSearchList;
};

} // namespace se
