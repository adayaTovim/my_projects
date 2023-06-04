#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#include "../network/udp.hpp"
#include "message.hpp"

namespace precious_stone {

static int createSocket();
static struct sockaddr_in bind(int a_sock, int a_port, const char* a_ip);

Udp::Udp(int a_port, const char* a_ip)
: m_socket(createSocket())
, m_sin(bind(m_socket, a_port, a_ip))
{
}

Udp::~Udp(){
    close(m_socket);
}

void Udp::send(Message const& a_message){
    ssize_t returnVal = sendto(m_socket, a_message.get().c_str(), a_message.get().size() + 1, 0, (struct sockaddr *)&m_sin, sizeof(m_sin));
    if (returnVal == -1){
        perror("sendto failed");
    }
}

Message Udp::receive(){
    socklen_t len = sizeof(m_sin);
    ssize_t returnVal = recvfrom(m_socket, m_buffer, 1024, 0, (struct sockaddr*)&m_sin, &len);
    if (returnVal < 0){
        perror("receive failed");
        close(m_socket);
    }
    m_buffer[returnVal] = '\0';
    return Message(m_buffer);
}


static int createSocket(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock >= 0);
    return sock;
}

static struct sockaddr_in bind(int a_sock, int a_port, const char* a_ip){
    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_ip);
    sin.sin_port = htons(a_port);

    //assert(bind(a_sock, (struct sockaddr *)&sin, sizeof(sin)) >= 0);    
    return sin;
}

} //precious_stone
