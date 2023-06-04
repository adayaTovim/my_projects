#include <string>
#include <iostream>

#include "console_destination.hpp"

namespace precious_stone {

ConsoleDestination::ConsoleDestination(std::ostream& a_os) 
: m_os{a_os} 
{
}

void ConsoleDestination::sendMessage(Message const& a_message) {
    std::string str = a_message.get();
    m_os << str << std::endl; 
}

} //precious_stone
