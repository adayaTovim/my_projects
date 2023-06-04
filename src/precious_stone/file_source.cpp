#include <fstream>
#include <string>
#include <cassert>
#include <iostream>

#include "file_source.hpp"

namespace precious_stone {

FileSource::FileSource(std::string a_filename)
: m_file(a_filename)
{
}

Message FileSource::getMessage()
{
    std::ifstream file(m_file);
    assert(file.is_open());    

    std::string buffer;
    std::string line;
    while (std::getline(file, line)) {
        buffer += line;
    }
    file.close();
    m_hasData = false; 
    return Message(buffer);
}

bool FileSource::isDone() const noexcept{
    return m_hasData;
}

} //precious_stone

