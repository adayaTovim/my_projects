#ifndef SOURCE_H_203
#define SOURCE_H_203

#include "message.hpp"

namespace precious_stone {

class Source{
public:
    virtual ~Source() = default;
    virtual Message getMessage() = 0;
    virtual bool isDone() const noexcept = 0; 

protected:
    Source() = default;
    Source(const Source& a_other) = default;
    Source& operator = (const Source& a_other) = default;
};

} //precious_stone

#endif //SOURCE_H_203
