#pragma once
#include <string>
#include <vector>
#include <cstdint>

#include "word_index.hpp"
#include "link_data.hpp"
#include "isearch.hpp"
#include "iupdate.hpp"

namespace se {

class DataBase : public IUpdate, public ISearch {
public:
    DataBase();
    DataBase(DataBase const& a_other) = delete;
    DataBase& operator=(DataBase const& a_other) = delete;
    ~DataBase() = default;

    void updateWordIndex(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter) override;
    void updateLinksGraph(std::string const& a_url, std::map<std::string, uint32_t> const& a_linkData) override;
    void updateExternalLinksCounter(uint32_t a_externalLinks) override;
    void updateVisitedLinksCounter() noexcept override;

    UrlTitleVec getWordData(std::string const& a_word) const override;
    uint32_t getWordsNumber() const override;
    uint32_t getWordUrlsNumber(std::string const& a_word) const override;

    uint32_t getLinkgraphSize() const override;
    uint32_t getExternalLinksCounter() const noexcept override;
    uint32_t getVisitedLinksCounter() const noexcept override;

private:
    WordIndex m_wordIndex;
    LinkData m_linkData;  
};

} // se