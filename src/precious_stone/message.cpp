#include <string>

#include "message.hpp"

namespace precious_stone {

Message::Message(const std::string& a_text)
: m_text(a_text)
{
}

std::string Message::get() const{
    return m_text;
}

} //precious_stone
