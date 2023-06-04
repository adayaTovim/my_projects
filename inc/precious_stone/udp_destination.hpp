#ifndef UDP_DESTINATION_H_203
#define UDP_DESTINATION_H_203

#include "destination.hpp"
#include "../network/udp.hpp"

namespace precious_stone {

class UdpDestination : public Destination {
public:
    explicit UdpDestination(int a_port, const char* a_ip);
    UdpDestination(const UdpDestination& a_other) = default;
    UdpDestination& operator = (const UdpDestination& a_other) = default;
    ~UdpDestination() = default;

    void sendMessage(Message const& a_message) override;

private:
    Udp m_udp;
};


} //precious_stone

#endif //UDP_DESTINATION_H_203

