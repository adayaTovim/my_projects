#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace se {

using UrlTitleVec = std::vector<std::tuple<std::string, std::string, uint32_t>>;

class ISearch {
public:
    virtual ~ISearch() = default;

    virtual UrlTitleVec getWordData(std::string const& a_word) const = 0;
    virtual uint32_t getWordsNumber() const = 0;
    virtual uint32_t getWordUrlsNumber(std::string const& a_word) const = 0;

    virtual uint32_t getLinkgraphSize() const = 0;
    virtual uint32_t getExternalLinksCounter() const noexcept = 0;
    virtual uint32_t getVisitedLinksCounter() const noexcept = 0;
    
};

} // se
