#include "NetworkModule\Packet.h"

CPacket::CPacket()
	: _Buffer(NULL)
{
}


CPacket::~CPacket()
{
	if (_Buffer != NULL)
	{
		delete[] _Buffer;
		_Buffer = NULL;
	}
}

bool CPacket::Initailize(CHAR* buffer, ULONG size, ULONG* remainderSize)
{
	// 4 BYTE (HEADER) + 4 BYTE (PACKET SIZE)
	// 만약에 Packet이 모자를 경우
	UINT baseSize = sizeof(BYTE) * 8;
	if (baseSize >= size) return false;

	// Packet이 전부 오지 않은 경우
	int packetSize = 0;
	CopyMemory(&packetSize, buffer + sizeof(BYTE) * 4, sizeof(BYTE) * 4);
	if (baseSize + packetSize > size) return false;

	// 나중에 POOL을 만들어서 사용을 한다.
	_Buffer = new CHAR[size];
	CopyMemory(_Buffer, buffer, baseSize + packetSize);
	*remainderSize = size - baseSize + packetSize;

	return true;
}