#include "NetworkCommon/DataBuffer.h"
#include <vcruntime_string.h>

CDataBuffer::CDataBuffer(int maxSize)
	: _Buffer(NULL)
{
	_StartIndex = 0;
	_Size = 0;

	Allocate(maxSize);
}

CDataBuffer::~CDataBuffer()
{
	if (_Buffer != NULL)
	{
		delete[] _Buffer;
		_Buffer = NULL;
	}
}

void CDataBuffer::Allocate(int maxSize)
{
	_MaxSize = maxSize;
	_Buffer = new unsigned char[maxSize];
}

bool CDataBuffer::Append(unsigned char* buffer, int size)
{
	if (_MaxSize < size)
	{
		unsigned char* TempBuffer = new unsigned char[_MaxSize + size];
		memcpy(TempBuffer, _Buffer, _MaxSize);
		_MaxSize = _MaxSize + size;

		delete[] _Buffer;
		_Buffer = TempBuffer;
	}

	if (_MaxSize - (_StartIndex + _Size) < size)
	{
		// 만일 새로 들어가야 할 Buffer가
		// 들어 갈 공간이 부족하다면 앞으로 땡긴다.
		memmove(_Buffer, _Buffer + _StartIndex, _Size);
		_StartIndex = 0;
	}

	if (_MaxSize - (_StartIndex + _Size) < size)
	{
		// 만일 새로 들어 갈 버퍼가 남은 공간 보다 클 경우
		// 새로 크게 할당한다.
		unsigned char* TempBuffer = new unsigned char[_MaxSize + size];
		memcpy(TempBuffer, _Buffer, _MaxSize);
		_MaxSize = _MaxSize + size;

		delete[] _Buffer;
		_Buffer = TempBuffer;
	}

	memcpy(_Buffer + (_StartIndex + _Size), buffer, size);

	_Size += size;

	return true;
}

void CDataBuffer::Pop(int size)
{
	_StartIndex += size;
	_Size -= size;
}

int CDataBuffer::GetDataSize()
{
	return _Size;
}

unsigned char* CDataBuffer::GetBuffer()
{
	return &_Buffer[_StartIndex];
}