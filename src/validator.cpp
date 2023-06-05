#include <regex>

#include "validator.hpp"

namespace se {

namespace {

bool isUrl(const std::string& a_url)
{
    // Regular expression pattern to match a URL
    std::regex urlRegex(
        R"(^(https?|ftp)://[^\s/$.?#].[^\s]*$)",
        std::regex::icase | std::regex::nosubs
    );

    return std::regex_match(a_url, urlRegex);
}

std::string createDomainUrl(std::string const& a_targetUrl) {
    std::size_t lastSlashIndex = a_targetUrl.find_last_of('/');
    if (lastSlashIndex != std::string::npos) {
        return a_targetUrl.substr(0, lastSlashIndex + 1);
    }
    return a_targetUrl;
}

} // namespace

uint32_t validateUrl(std::map<std::string, uint32_t>& a_mapUrl, std::string const& a_targetUrl)
{
    uint32_t counter = 0;

    if (a_mapUrl.empty() || !isUrl(a_targetUrl)) {
        return 0;
    }
    
    std::string domainUrl = createDomainUrl(a_targetUrl);

    auto it = a_mapUrl.begin();
    while(it !=  a_mapUrl.end()) {
        const std::string& url = it->first;
        if(url.substr(0, domainUrl.size()) != domainUrl ) {
            it = a_mapUrl.erase(it);
            ++counter;
        } 
        else {
            ++it;
        }
    }

    return counter;
}

} // namespace se

