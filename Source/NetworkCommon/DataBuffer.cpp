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
		// ���� ���� ���� �� Buffer��
		// ��� �� ������ �����ϴٸ� ������ �����.
		memmove(_Buffer, _Buffer + _StartIndex, _Size);
		_StartIndex = 0;
	}

	if (_MaxSize - (_StartIndex + _Size) < size)
	{
		// ���� ���� ��� �� ���۰� ���� ���� ���� Ŭ ���
		// ���� ũ�� �Ҵ��Ѵ�.
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