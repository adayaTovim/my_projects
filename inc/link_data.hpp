#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace se {


class LinkData {
public:
    LinkData();
    LinkData(LinkData const& a_other) = delete;
    LinkData& operator=(LinkData const& a_other) = delete;
    ~LinkData() = default;

    void updateLinkGraph(std::string const& a_url, std::map<std::string, uint32_t> const& a_linkData);
    void updateExternalLinksCounter(uint32_t a_externalLinks);
    void updateVisitedLinksCounter() noexcept;

    uint32_t getLinkgraphSize() const;
    uint32_t getExternalLinksCounter() const noexcept;
    uint32_t getVisitedLinksCounter() const noexcept;

private:
    using LinkGraph = std::map<std::string, std::map< std::string, uint32_t>>;
    LinkGraph m_linkGraph;
    uint32_t m_externalLinksCounter;
    uint32_t m_visitedLinksCounter;
};

} //se
