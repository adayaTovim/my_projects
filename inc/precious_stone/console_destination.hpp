
#ifndef CONSOLE_DESTINATION_H_203
#define CONSOLE_DESTINATION_H_203

#include "destination.hpp"
#include "message.hpp"

namespace precious_stone {

class ConsoleDestination : public Destination {
public:
    explicit ConsoleDestination(std::ostream &a_os = std::cout);
    ConsoleDestination(const ConsoleDestination& a_other) = default;
    ConsoleDestination& operator = (const ConsoleDestination& a_other) = default;
    ~ConsoleDestination() = default;

    void sendMessage(Message const& a_message) override;

private:
    std::ostream& m_os;
};


} //precious_stone

#endif //CONSOLE_DESTINATION_H_203


