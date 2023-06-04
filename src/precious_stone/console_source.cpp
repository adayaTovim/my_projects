#include <iostream>
#include <string>

#include "console_source.hpp"

namespace precious_stone {

Message ConsoleSource::getMessage(){
    std::string input;
    std::getline(std::cin, input);
    Message newMessage(input); 
    if(newMessage.get() == "0") {
        m_hasData = false;
    }
    return Message(input); 
}

bool ConsoleSource::isDone() const noexcept{
    return m_hasData;
}

}//precious_stone
