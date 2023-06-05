#include <fstream>  			// std::ifstream
#include <jsoncpp/json/json.h> 	// json header

#include "json_file_reader.hpp" // Current header

namespace se {

JsonFile::JsonFile(const std::string& a_filename)
: m_filename(a_filename)
, m_urls()
, m_crawlMode()
, m_depth()
, m_maxPages()
{
    std::ifstream reader(a_filename);
    if (!reader.is_open()) {
        throw std::runtime_error("Could not open configuration file");
    }

    Json::Value root;
    reader >> root;

    Json::Value urlsJson = root["url"];
    for (const auto& url : urlsJson) {
        m_urls.push_back(url.asString());
    }

    m_crawlMode = root.get("mode", "DFS").asString();
    m_depth = std::stoi(root.get("depth", "2").asString());
    m_maxPages = std::stoi(root.get("pages", "20").asString());
	m_totalSearchList = std::stoi(root.get("search_list", "0").asString());
}

const std::vector<std::string>& JsonFile::getUrls() const
{
    return m_urls;
}

std::string& JsonFile::crawlMode()
{
    return m_crawlMode;
}

std::uint16_t JsonFile::depth() const
{
    return m_depth;
}

std::uint32_t JsonFile::maxPages() const
{
    return m_maxPages;
}

std::uint32_t JsonFile::totalSearchList() const
{
	return m_totalSearchList;
}


} // namespace se
