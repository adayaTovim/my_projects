#ifndef FILE_SOURCE_H_203
#define FILE_SOURCE_H_203

#include <fstream> //ifstream

#include "source.hpp"
#include "message.hpp"

namespace precious_stone {

class FileSource : public Source {
public:
    explicit FileSource(std::string a_filename);
    FileSource(const FileSource& a_other) = default;
    FileSource& operator = (const FileSource& a_other) = default;
    ~FileSource() override = default;
    
    Message getMessage() override;
    bool isDone() const noexcept override; 

private:
    bool m_hasData = true;
    std::string m_file;
};


} //precious_stone

#endif //FILE_SOURCE_H_203

