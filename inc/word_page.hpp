#pragma once
#include <cstdint>
#include <string>
#include <cstdint>

namespace se {

class WordPage{
public:
    WordPage() = delete;
    explicit WordPage(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter);
    WordPage(WordPage const& a_other) = default;
    WordPage& operator=(WordPage const& a_other) = default;
    ~WordPage() = default;

    std::string getTitle() const noexcept;
    std::string getUrl() const noexcept;
    std::string getWord() const noexcept;
    uint32_t getCounter() const noexcept;

private:
    std::string m_word;
    std::string m_title;
    std::string m_url;
    uint32_t m_counter;
};

} //se
