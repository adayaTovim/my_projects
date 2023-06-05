#include <cstdint>
#include <string>
#include <cstdint>
#include "word_page.hpp"

namespace se {

WordPage::WordPage(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter)
: m_word(a_word)
, m_title(a_title)
, m_url(a_url)
, m_counter(a_counter)
{

}

std::string WordPage::getTitle() const noexcept 
{
    return m_title;
}

std::string WordPage::getUrl() const noexcept
{
    return m_url;
}

std::string WordPage::getWord() const noexcept
{
    return m_word;
}

uint32_t WordPage::getCounter() const noexcept
{
    return m_counter;
}


} //se