
#include <string>

#include "convert_vowel.hpp"

namespace precious_stone {


Message ConvertVowel::messageEncoder(Message& a_message){
    std::string text = a_message.get();
    int sizeMessage = text.size();
    
    for(int i = 0; i < sizeMessage; ++i){
        if (text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || 
                text[i] == 'u' || text[i] == 'A' || text[i] == 'E' || text[i] == 'I' || 
                text[i] == 'O' || text[i] == 'U'){
            text[i] = '*';
        }       
    }
    return Message(text);
}

} //precious_stone









