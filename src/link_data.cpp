#include "link_data.hpp"
#include "string_utils.hpp"

namespace se {

LinkData::LinkData()
: m_linkGraph()
, m_externalLinksCounter(0)
, m_visitedLinksCounter(0)
{
}

void LinkData::updateLinkGraph(std::string const& a_url, std::map<std::string, uint32_t> const& a_linkData)
{   
    // check if the this page url already exists
    auto it = m_linkGraph.find(a_url);
    if (it != m_linkGraph.end()) {
        // this page url already exists, what to do??
        it->second = a_linkData; //change the map
        //or it->second->second += 1;
    } else {
        // new page
        m_linkGraph.insert({a_url, a_linkData});
    }
}

void LinkData::updateVisitedLinksCounter() noexcept
{
    ++m_visitedLinksCounter;
}

void LinkData::updateExternalLinksCounter(uint32_t a_externalLinks)
{
    m_externalLinksCounter += a_externalLinks;
}

uint32_t LinkData::getLinkgraphSize() const
{
    return m_linkGraph.size();
}

uint32_t LinkData::getExternalLinksCounter() const noexcept
{
    return m_externalLinksCounter;
}

uint32_t LinkData::getVisitedLinksCounter() const noexcept
{
    return m_visitedLinksCounter;
}

} // namespace se