#pragma once

#include "base.h"

#define ADDITIONAL_SIZE 10 //1024 * 128

#define MAX_SIZE		1024 * 1024 // 1M

namespace Bullet 
{
class Buffer :public IBase
{
public:
	virtual unsigned int GetEmptySize();
	void ReAllocBuffer(unsigned int dataLength);
	unsigned int GetEndIndex() const
	{
		return _endIndex;
	}

	unsigned int GetBeginIndex() const
	{
		return _beginIndex;
	}

	unsigned int GetTotalSize() const
	{
		return _bufferSize;
	}

    void Base() override
    {}

protected:
	char* _buffer{ nullptr };
	unsigned int _beginIndex{ 0 }; 
	unsigned int _endIndex{ 0 };

	unsigned int _bufferSize{ 0 };
};
}