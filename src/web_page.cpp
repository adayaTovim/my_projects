#include <string>   // std::string
#include <map>      // std::map
#include <cstdint>  // std::uint32_t

#include "web_page.hpp" // Current header

namespace se {

WebPage::WebPage(const std::string& a_title, const std::string& a_url)
: m_title(a_title)
, m_url(a_url)
, m_words()
, m_links()
{}

void WebPage::insertWord(const std::string& a_word)
{
    if(m_words[a_word]) {
        m_words[a_word] += 1;
    }
    else {
        m_words[a_word] = 1;
    }
}

void WebPage::insertLink(const std::string& a_link)
{
    if(m_links[a_link]) {
        m_links[a_link] += 1;
    }
    else {
        m_links[a_link] = 1;
    }
}

uint32_t WebPage::getWordCount(const std::string& a_word) noexcept
{
    return m_words[a_word];
}

uint32_t WebPage::getLinkCount(const std::string& a_link) noexcept
{
    return m_links[a_link];
}

uint32_t WebPage::uniqueWordsCount() const noexcept
{
    uint32_t sum = 0;

    for(const auto& word : m_words) {
        if (word.second > 0) {
            sum += 1;
        }
    }

    return sum;
}

uint32_t WebPage::uniqueLinksCount() const noexcept
{
    uint32_t sum = 0;

    for(const auto& link : m_links) {
        if (link.second > 0) {
            sum += 1;
        }
    }

    return sum;
}

uint32_t WebPage::totalWordsCount() const noexcept
{
    uint32_t sum = 0;

    for(const auto& word : m_words) {
        sum += word.second;
    }

    return sum;
}

uint32_t WebPage::totalLinksCount() const noexcept
{
    uint32_t sum = 0;

    for(const auto& link : m_links) {
        sum += link.second;
    }

    return sum;
}

std::string WebPage::title() const noexcept
{
    return m_title;
}

std::string WebPage::url() const noexcept
{
    return m_url;
}

std::map<std::string, uint32_t>& WebPage::words() noexcept
{
    return m_words;
}

std::map<std::string, uint32_t>& WebPage::links() noexcept
{
    return m_links;
}

} // namespace se
