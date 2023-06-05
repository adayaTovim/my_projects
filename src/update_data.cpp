
#include "update_data.hpp"
#include "validator.hpp"

namespace se {

UpdateData::UpdateData(IUpdate& a_updater)
: m_updater(a_updater)
{
}

void UpdateData::storeAllData(WebPage& a_page)
{
    if(a_page.links().empty() && a_page.words().empty()) {
        return;
    }
    
    storePageData(a_page);
    storeCounterExternalLinks(a_page);
    storeLinkGraph(a_page);
    m_updater.updateVisitedLinksCounter();
}

void UpdateData::storePageData(WebPage& a_page) 
{    
    const auto& words = a_page.words();
    for (const auto& word_count : words) {
        const auto& word = word_count.first;
        const auto& count = word_count.second;
        m_updater.updateWordIndex(word, a_page.url(), a_page.title(), count);
    }
}

void UpdateData::storeCounterExternalLinks(WebPage& a_page) 
{    
    uint32_t counter = validateUrl(a_page.links(), a_page.url());
    m_updater.updateExternalLinksCounter(counter);
}

void UpdateData::storeLinkGraph(WebPage& a_page) 
{
    m_updater.updateLinksGraph(a_page.url(), a_page.links());
}

} // namespace se

