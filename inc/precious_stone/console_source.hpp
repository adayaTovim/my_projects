#ifndef CONSOLE_SOURCE_H_203
#define CONSOLE_SOURCE_H_203

#include "source.hpp"
#include "message.hpp"

namespace precious_stone {

class ConsoleSource : public Source {
public:
    ConsoleSource()= default;
    ConsoleSource(const ConsoleSource& a_other) = default;
    ConsoleSource& operator = (const ConsoleSource& a_other) = default;
    ~ConsoleSource() override = default;
    
    Message getMessage() override;
    bool isDone() const noexcept override; 

private:
bool m_hasData = true;
};

} //precious_stone

#endif //CONSOLE_SOURCE_H_203

