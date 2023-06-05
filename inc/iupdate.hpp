#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <map>

namespace se {

class IUpdate {
public:
    virtual ~IUpdate() = default;

    virtual void updateWordIndex(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter) = 0;
    virtual void updateLinksGraph(std::string const& a_url, std::map<std::string, uint32_t> const& a_linkData) = 0;
    virtual void updateExternalLinksCounter(uint32_t a_externalLinks) = 0;
    virtual void updateVisitedLinksCounter() noexcept = 0;
};

} // se
