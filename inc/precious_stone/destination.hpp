#ifndef DESTINATION_H_203
#define DESTINATION_H_203

#include "message.hpp"

namespace precious_stone {

class Destination{
public:

    virtual ~Destination() = default;
    virtual void sendMessage(Message const& a_message) = 0;

protected:
    Destination() = default;
    Destination(const Destination& a_other) = default;
    Destination& operator = (const Destination& a_other) = default;


private:

};

} //precious_stone

#endif //DESTINATION_H_203
