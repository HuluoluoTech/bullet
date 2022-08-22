#pragma once

// #include <boost/asio/streambuf.hpp>
#include <iostream>
#include "buffer.h"

namespace Bullet
{

#pragma pack(push)
#pragma pack(4)

struct PacketHead {
	unsigned short MsgId;
};

#pragma pack(pop)

#define DEFAULT_PACKET_BUFFER_SIZE	1024 * 10

using MsgID = unsigned short;
using DataLen = size_t;

class Packet : public Buffer
{
public:
    Packet();
    Packet(const MsgID MsgId);
    ~Packet();

    void Base() override;

    void AppendBuffer(const char* pBuffer);
    void ClearBuffer();

    MsgID GetMsgID();
    DataLen GetBufferDataLen();

    template<class ProtoClass>
    ProtoClass DeserializeToProto()
    {
  		ProtoClass proto;
		proto.ParsePartialFromArray(GetBuffer(), GetDataLength());
		return proto;
    }

    template<class ProtoClass>
    void SerializeToBuffer(ProtoClass& protoClase)
    {
		auto total = protoClase.ByteSizeLong();
		while (GetEmptySize() < total)
		{
			ReAllocBuffer();
		}

		protoClase.SerializePartialToArray(GetBuffer(), total);
		FillData(total);
    }


	void CleanBuffer();

	char* GetBuffer() const;
	unsigned short GetDataLength() const;
	int GetMsgId() const;
	void FillData(unsigned int size);
	void ReAllocBuffer();

private:
    MsgID m_msgId;
    // boost::asio::streambuf *m_streambuf;
    char* buff;
};
}