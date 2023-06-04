#include <fstream>
#include <string>
#include <cassert>

#include "file_destination.hpp"

namespace precious_stone {

FileDestination::FileDestination(std::string a_filename)
: m_file(a_filename)
{
}

void FileDestination::sendMessage(Message const& a_message){
    std::ofstream file(m_file, std::ios_base::app);
    assert(file.is_open());
    file << a_message.get() << std::endl;
    file.close();
}

} //precious_stone
