#include <string>
#include <vector>
#include <cstdint>
#include "data_base.hpp"
#include "word_index.hpp"
#include "link_data.hpp"

namespace se {

DataBase::DataBase()
: m_wordIndex()
, m_linkData()
{

}

void DataBase::updateWordIndex(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter) 
{
    m_wordIndex.setWordIndex(a_word, a_url, a_title, a_counter);
}  

void DataBase::updateLinksGraph(std::string const& a_url, std::map<std::string, uint32_t> const& a_linkData)
{
    m_linkData.updateLinkGraph(a_url, a_linkData);
}

void DataBase::updateExternalLinksCounter(uint32_t a_externalLinks)
{
    m_linkData.updateExternalLinksCounter(a_externalLinks);
}

void DataBase::updateVisitedLinksCounter() noexcept 
{
    m_linkData.updateVisitedLinksCounter();
}

UrlTitleVec DataBase::getWordData(std::string const& a_word) const 
{
    return m_wordIndex.getIndexedWordData(a_word);
}

uint32_t DataBase::getWordsNumber() const
{
    return m_wordIndex.getNumOfWords();
}

uint32_t DataBase::getWordUrlsNumber(std::string const& a_word) const
{
    return m_wordIndex.getNumWordOfUrls(a_word);
}

uint32_t DataBase::getLinkgraphSize() const
{
    return m_linkData.getLinkgraphSize();
}

uint32_t DataBase::getExternalLinksCounter() const noexcept
{
    return m_linkData.getExternalLinksCounter();
}

uint32_t DataBase::getVisitedLinksCounter() const noexcept
{
    return m_linkData.getVisitedLinksCounter();
}

} // se
