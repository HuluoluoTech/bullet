#include "packet.h"
#include <sstream> // std::ostream
#include <cstring>

namespace Bullet 
{
Packet::Packet()
{
	m_msgId = 0;
	CleanBuffer();

	_bufferSize = DEFAULT_PACKET_BUFFER_SIZE;
	_beginIndex = 0;
	_endIndex = 0;
	_buffer = new char[_bufferSize];
}

Packet::Packet(const MsgID msgId)
{
	m_msgId = msgId;
	CleanBuffer();

	_bufferSize = DEFAULT_PACKET_BUFFER_SIZE;
	_beginIndex = 0;
	_endIndex = 0;
	_buffer = new char[_bufferSize];
}

Packet::~Packet()
{
	CleanBuffer();
}

void Packet::Base()
{
	m_msgId = 0;
	_beginIndex = 0;
	_endIndex = 0;
}

void Packet::AddBuffer(const char* pBuffer, const unsigned int size)
{
	while (GetEmptySize() < size)
	{		
		ReAllocBuffer();
	}

	::memcpy(_buffer, pBuffer, size);
	FillData(size);
}

void Packet::CleanBuffer()
{
	if (_buffer != nullptr)
		delete[] _buffer;

	_beginIndex = 0;
	_endIndex = 0;
	_bufferSize = 0;
}

char* Packet::GetBuffer() const
{
	return _buffer;
}

unsigned short Packet::GetDataLength() const
{
	return _endIndex - _beginIndex;
}

int Packet::GetMsgId() const
{
	return m_msgId;
}

void Packet::FillData(const unsigned int size)
{
	_endIndex += size;
}

void Packet::ReAllocBuffer()
{
	Buffer::ReAllocBuffer(_endIndex - _beginIndex);
}

}



