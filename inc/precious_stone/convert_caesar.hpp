#ifndef CONVERT_CAESAR_H_203
#define CONVERT_CAESAR_H_203

#include "encoder.hpp"

namespace precious_stone {

class ConvertCaesar : public Encoder {
public:
    ConvertCaesar() = default;
    ConvertCaesar(const ConvertCaesar& a_other) = default;
    ConvertCaesar& operator = (const ConvertCaesar& a_other) = default;
    ~ConvertCaesar() = default;
    
    Message messageEncoder(Message& a_message) override;
};

} //precious_stone

#endif //CONVERT_CAESAR_H_203
