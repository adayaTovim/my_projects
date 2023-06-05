#pragma once

#include <string> // std::string

namespace se {

class Parser {
public:
    virtual ~Parser() = default;

    virtual std::string getTitle() = 0;
    virtual std::string getLinks() = 0;
    virtual std::string getParagraphsText() = 0;
};

} // namespace se
