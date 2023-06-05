#include "crawler_mannager.hpp" // Current header
#include "web_page.hpp"         // WebPage header

namespace se {

CrawlerManager::CrawlerManager(ConfigurationReader& a_config, IUpdate& a_updater)
: m_queue()
, m_crawler(a_updater)
, m_urls()
, m_config(a_config)
{
    auto urls = m_config.getUrls();
    for (const auto& url : urls) {
        m_urls.insert(url);
        m_queue.push_back(UrlAndDepth{url, 0});
    }
}

uint32_t CrawlerManager::startCrawling()
{
    uint32_t maxPages = m_config.maxPages();
    uint16_t depth = m_config.depth();

    while (!m_queue.empty() && maxPages > 0) {
        auto urlAndDepth = m_queue.front();
        uint16_t currentDepth = urlAndDepth.m_depth;

        auto page = m_crawler.crawlOneUrl(urlAndDepth.m_url);
        m_queue.pop_front();
        if(page.title() == "<empty_title>") {
            continue;
        }

        --maxPages;
        auto links = page.links();

        if(currentDepth <= depth) {
            for(auto itr = links.rbegin(); itr != links.rend(); ++itr) {
                const auto& link = *itr;
                if(m_urls.find(link.first) == m_urls.end()) {
                    m_queue.push_front(UrlAndDepth{link.first, static_cast<uint16_t>(currentDepth + 1)});
                    m_urls.insert(link.first);
                }
            }
        }
    }

    return m_crawler.getFailedLinks();
}


} // namespace se
