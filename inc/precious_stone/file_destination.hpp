#ifndef FILE_DESTINATION_H_203
#define FILE_DESTINATION_H_203

#include "destination.hpp"
#include "message.hpp"

namespace precious_stone {

class FileDestination : public Destination {
public:
    explicit FileDestination(std::string a_filename);
    FileDestination(const FileDestination& a_other) = default;
    FileDestination& operator = (const FileDestination& a_other) = default;
    ~FileDestination() = default;

    void sendMessage(Message const& a_message) override;

private:
    std::string m_file;
};


} //precious_stone

#endif //FILE_DESTINATION_H_203


