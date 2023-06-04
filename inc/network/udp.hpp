#ifndef UDP_H_203
#define UDP_H_203

#include <arpa/inet.h>

#include "message.hpp"

namespace precious_stone {

class Udp {
public:
    explicit Udp(int a_port, const char* a_ip);
    Udp(const Udp& a_other) = default;
    Udp& operator = (const Udp& a_other) = delete;
    ~Udp(); 

    void send(Message const& a_message);
    Message receive();

private:
    int m_socket;
    struct sockaddr_in m_sin;
    char m_buffer[1024];
};

} //precious_stone

#endif //UDP_H_203


