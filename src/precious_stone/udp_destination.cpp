#include<iostream>

#include "udp_destination.hpp"
#include "message.hpp"

namespace precious_stone {

UdpDestination::UdpDestination(int a_port, const char* a_ip)
: m_udp(Udp(a_port, a_ip))
{
}

void UdpDestination::sendMessage(Message const& a_message){
    m_udp.send(a_message);
}

} //precious_stone
