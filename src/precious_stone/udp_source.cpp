#include<iostream>

#include "udp_source.hpp"
#include "message.hpp"

namespace precious_stone {

UdpSource::UdpSource(int a_port, const char* a_ip)
: m_udp(Udp(a_port, a_ip))
{
}

Message UdpSource::getMessage(){
    Message newMessage(m_udp.receive().get());
    return newMessage;
}

bool UdpSource::isDone() const noexcept{
    return m_hasData;
}

} //precious_stone
