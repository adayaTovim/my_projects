
#include <string>

#include <string>

#include "convert_capitalize.hpp"

namespace precious_stone {


Message ConvertCapitalize::messageEncoder(Message& a_message){
    std::string text = a_message.get();
    int sizeMessage = text.size();
    for(int i = 0; i < sizeMessage; ++i){
        if (i == 0 || text[i-1] == ' '){
            text[i] = toupper(text[i]);
        }       
    }
    return Message(text);
}



} //precious_stone

