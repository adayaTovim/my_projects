#ifndef CONVERT_CAPITALIZE_H_203
#define CONVERT_CAPITALIZE_H_203

#include "encoder.hpp"

namespace precious_stone {

class ConvertCapitalize : public Encoder {
public:
    ConvertCapitalize() = default;
    ConvertCapitalize(const ConvertCapitalize& a_other) = default;
    ConvertCapitalize& operator = (const ConvertCapitalize& a_other) = default;
    ~ConvertCapitalize() = default;
    
    Message messageEncoder(Message& a_message) override;
};

} //precious_stone

#endif //CONVERT_CAPITALIZE_H_203
