#include <string>
#include <queue>

#include "black_box.hpp"

namespace precious_stone{

BlackBox::BlackBox(Source& a_source, Destination& a_destination, Encoder& a_encoder)
: m_source(a_source)
, m_destination(a_destination)
, m_encoder(a_encoder)
{
}

void BlackBox::run(){
    while (m_source.isDone()){  ///?????
        Message newMessage = m_source.getMessage();
        newMessage = m_encoder.messageEncoder(newMessage);
        m_destination.sendMessage(newMessage);
    }
}


} //precious_stone
