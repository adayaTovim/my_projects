#include <string>

#include "convert_caesar.hpp"

namespace precious_stone {

Message ConvertCaesar::messageEncoder(Message& a_message){
    std::string text = a_message.get();
    int sizeMessage = text.size();
    int shiftAmount = 13; 
    for(int i = 0; i < sizeMessage; ++i){
        if (isalpha(text[i])){
            char shiftedChar;
            if(isupper(text[i])){
                shiftedChar = static_cast<char>((text[i] - 'A' + shiftAmount) % 26 + 'A');
            }
            else{
                shiftedChar = static_cast<char>((text[i] - 'a' + shiftAmount) % 26 + 'a');
            }
            text[i] = shiftedChar;       
        }      
    }
    return Message(text);
}

} //precious_stone

