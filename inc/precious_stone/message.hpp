#ifndef MESSAGE_H_203
#define MESSAGE_H_203

#include <string>

namespace precious_stone {

class Message{
public:
    Message() = delete;
    explicit Message(const std::string& a_text);
    Message(const Message& a_other) = default;
    Message& operator = (const Message& a_other) = default;
    ~Message() = default;

    std::string get() const;
    //void set(std::string a_text);

private:
    std::string m_text;
};



} //precious_stone

#endif //MESSAGE_H_203
