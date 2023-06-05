#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <tuple>

#include "word_page.hpp"

namespace se {

using WordsMap = std::unordered_map<std::string, std::vector<WordPage>>;
using UrlTitleVec = std::vector<std::tuple<std::string, std::string, uint32_t>>;

class WordIndex {
public:
    WordIndex();
    WordIndex(WordIndex const& a_other) = delete;
    WordIndex& operator=(WordIndex const& a_other) = delete;
    ~WordIndex() = default;

    void setWordIndex(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter);
    UrlTitleVec getIndexedWordData(std::string const& a_word) const;

    uint32_t getNumOfWords() const;
    uint32_t getNumWordOfUrls(std::string const& a_word) const;

private:
    void insertPage(WordPage const& a_page, std::vector<WordPage>& a_pages);

private:
    WordsMap m_wordIndex;
    
};

} //se