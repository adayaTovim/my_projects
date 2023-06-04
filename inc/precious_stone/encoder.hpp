#ifndef ENCODER_H_203
#define ENCODER_H_203

#include "message.hpp"

namespace precious_stone {

class Encoder{
public:
    virtual ~Encoder() = default;
    virtual Message messageEncoder(Message& a_message) = 0;

protected:
    Encoder() = default;
    Encoder(const Encoder& a_other) = default;
    Encoder& operator = (const Encoder& a_other) = default;

private:
    //m_encoderType;
};

} //precious_stone

#endif //ENCODER_H_203
