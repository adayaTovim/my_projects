#ifndef UDP_SOURCE_H_203
#define UDP_SOURCE_H_203

#include "source.hpp"
#include "../network/udp.hpp"

namespace precious_stone {

class UdpSource : public Source {
public:
    explicit UdpSource(int a_port, const char* a_ip);
    UdpSource(const UdpSource& a_other) = default;
    UdpSource& operator = (const UdpSource& a_other) = default;
    ~UdpSource() override = default;
    
    Message getMessage() override;
    bool isDone() const noexcept override; 

private:
    bool m_hasData = true;
    Udp m_udp;
};


} //precious_stone

#endif //UDP_SOURCE_H_203

