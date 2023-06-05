#pragma once

#include <string>           // std::string
#include <vector>           // std::vector
#include <deque>            // std::deque
#include <unordered_set>    // std::unordered_set
#include <cstdint>          // std::uint32_t, std::uint16_t

#include "crawler.hpp"          // Crawler header
#include "json_file_reader.hpp" // Json header
#include "update_data.hpp"      // UpdateData header
#include "iupdate.hpp"          // IUpdate header

namespace se {

struct UrlAndDepth {
    std::string m_url;
    uint16_t m_depth;
};

class CrawlerManager {
public:
    explicit CrawlerManager(ConfigurationReader& a_config, IUpdate& a_updater);
    CrawlerManager(const CrawlerManager& a_other) = delete;
    CrawlerManager& operator=(const CrawlerManager& a_other) = delete;
    ~CrawlerManager() = default;

    uint32_t startCrawling();

private:
    std::deque<UrlAndDepth> m_queue;
    Crawler m_crawler;
    std::unordered_set<std::string> m_urls;
    ConfigurationReader& m_config;
};

} // namespace se
