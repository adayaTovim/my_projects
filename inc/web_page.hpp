#pragma once

#include <string>   // std::string
#include <map>    // std::map
#include <cstdint>  // std::uint32_t

namespace se {

class WebPage {
public:
    explicit WebPage(const std::string& a_title, const std::string& a_url);
    WebPage(const WebPage& a_other) = default;
    WebPage& operator=(const WebPage& a_other) = delete;
    ~WebPage() = default;

    void insertWord(const std::string& a_word);
    void insertLink(const std::string& a_link);

    uint32_t getWordCount(const std::string& a_word) noexcept;
    uint32_t getLinkCount(const std::string& a_link) noexcept;
    uint32_t uniqueWordsCount() const noexcept;
    uint32_t uniqueLinksCount() const noexcept;
    uint32_t totalWordsCount() const noexcept;
    uint32_t totalLinksCount() const noexcept;

    std::string title() const noexcept;
    std::string url() const noexcept;
    std::map<std::string, uint32_t>& links() noexcept;
    std::map<std::string, uint32_t>& words() noexcept;

private:
    std::string m_title;
    std::string m_url;
    std::map<std::string, uint32_t> m_words;
    std::map<std::string, uint32_t> m_links;
};

} // namespace se
