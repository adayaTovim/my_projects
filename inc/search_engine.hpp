#pragma once

#include <string> // std::string

namespace se {

class SearchEngine {
public:
    SearchEngine() = default;
    SearchEngine(const SearchEngine&) = delete;
    SearchEngine& operator=(const SearchEngine& a_other) = delete;
    ~SearchEngine() = default;

    void execute(std::string const& a_fileName);
};

} // namespace s

