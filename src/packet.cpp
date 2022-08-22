#include "packet.h"

namespace Bullet 
{
Packet::Packet()
{
}

Packet::Packet(MsgID msgId)
{
    m_msgId = msgId;
}

Packet::~Packet()
{}

void Packet::Base()
{}


boost::asio::streambuf& Packet::GetBuffer()
{
    return m_streambuf;
}

void Packet::ClearBuffer()
{}

MsgID Packet::GetMsgID()
{
    return m_msgId;
}

DataLen Packet::GetBufferDataLen()
{
    return m_streambuf.data().size();
}

}



