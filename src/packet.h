#pragma once

#include "base.h"
#include <boost/asio/streambuf.hpp>

namespace Bullet
{

#pragma pack(push)
#pragma pack(4)

struct PacketHead {
	unsigned short MsgId;
};

#pragma pack(pop)

using MsgID = unsigned short;
using DataLen = size_t;

class Packet : public IBase
{
public:
    Packet();
    Packet(const MsgID MsgId);
    ~Packet();

    void Base() override;

    boost::asio::streambuf& GetBuffer();
    void ClearBuffer();

    MsgID GetMsgID();
    DataLen GetBufferDataLen();

private:
    MsgID m_msgId;
    boost::asio::streambuf m_streambuf;
};
}