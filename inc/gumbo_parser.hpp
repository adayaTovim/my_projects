#pragma once

#include <string>   // std::string
#include <sstream>  // std::stringstream
#include <gumbo.h>  // Gumbo Parser Library

#include "parser.hpp" // Inheritance header

namespace se {

class GumboParser : public Parser {
public:
    GumboParser();
    GumboParser(const GumboParser& a_other) = delete;
    GumboParser& operator=(const GumboParser& a_other) = delete;
    ~GumboParser() = default;

    void parse(const std::ostringstream& a_html);
    void freeParse();

    std::string getTitle() override;
    std::string getLinks() override;
    std::string getParagraphsText() override;

private:
    GumboOutput* m_extractor;
    GumboNode* m_root;
};

} // namespace se
