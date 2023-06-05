#include <algorithm>

#include "word_index.hpp"
#include "string_utils.hpp"

namespace se
{

namespace {

bool isUrlExist(const WordPage& a_page, const std::vector<WordPage>& a_pageVector) 
{
    for (const auto& p : a_pageVector) {
        if(p.getUrl() == a_page.getUrl()) {
            return true;
        }
    }

    return false;
}

} // empty namespace for static functions

WordIndex::WordIndex()
: m_wordIndex()
{
}
    
void WordIndex::setWordIndex(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter) 
{
    std::string lowerWord = a_word;
    lowerWord = toLowercase(lowerWord);
    lowerWord = removeNoneLetters(lowerWord);
    if (lowerWord.empty()) {
        return;
    }

    WordPage page{lowerWord, a_url, a_title, a_counter};
    
    // check if the word already exists
    auto it = m_wordIndex.find(lowerWord);
    if (it != m_wordIndex.end()) {
        // word already exists, add the page to its existing vector
        if(!isUrlExist(page, it->second)) {
            insertPage(page, it->second);
        }
    } else {
        // new word, create new vector
        std::vector<WordPage> newPageVector;
        newPageVector.push_back(page);
        m_wordIndex.insert({lowerWord, newPageVector});
    }
}

void WordIndex::insertPage(WordPage const& a_page, std::vector<WordPage>& a_pages) //insert page by its counter
{
    auto it = a_pages.begin();
    while(it != a_pages.end() && it -> getCounter() > a_page.getCounter()) {
        ++it;
    }
    a_pages.insert(it, a_page);
}

UrlTitleVec WordIndex::getIndexedWordData(std::string const& a_word) const
{
    std::string lowerWord = a_word;
    lowerWord = toLowercase(lowerWord);
    lowerWord = removeNoneLetters(lowerWord);

    UrlTitleVec v;
    auto it = m_wordIndex.find(lowerWord);

    if (it != m_wordIndex.end()) {
        auto vecIt = it->second.begin();
        while(vecIt!= it->second.end()) {
            v.push_back(std::make_tuple(vecIt->getTitle(), vecIt->getUrl(), vecIt->getCounter()));
            ++vecIt;
        }
    } 
    return v;
}

uint32_t WordIndex::getNumOfWords() const
{
    return m_wordIndex.size();
}

uint32_t WordIndex::getNumWordOfUrls(std::string const& a_word) const
{
    std::string lowerWord = a_word;
    lowerWord = toLowercase(lowerWord);
    lowerWord = removeNoneLetters(lowerWord);
    
    auto it = m_wordIndex.find(lowerWord);

    if (it!= m_wordIndex.end()) {
        return it->second.size();
    } else {
        return 0;
    }
}

} // namespace se
