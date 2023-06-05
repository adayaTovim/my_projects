#include <algorithm>

#include "string_utils.hpp"

namespace se {

std::string toLowercase(const std::string& a_string) {
    std::string result(a_string);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
}

std::string removeNoneLetters(const std::string& a_string)
{
    std::string result(a_string);
    result.erase(
        std::remove_if(result.begin(), result.end(), [](unsigned char c) {
            return !std::isalpha(c);
        }),
        result.end()
    );
    return result;
}

} // namespace se