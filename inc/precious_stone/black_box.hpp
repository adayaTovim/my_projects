#ifndef BLACK_BOX_H_203
#define BLACK_BOX_H_203

#include "message.hpp"
#include "destination.hpp"
#include "source.hpp"
#include "encoder.hpp"

namespace precious_stone {

class BlackBox{
public:
    BlackBox() = delete;
    explicit BlackBox(Source& a_source, Destination& a_destination, Encoder& a_encoder);
    BlackBox(const BlackBox& a_other) = default;
    BlackBox& operator = (const BlackBox& a_other) = default;
    ~BlackBox() = default;

    void run();
    
private:
    Source& m_source;
    Destination& m_destination;
    Encoder& m_encoder;
};

} //precious_stone

#endif //BLACK_BOX_H_203
