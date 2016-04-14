#pragma once
#include "NetworkCommon\Define.h"

class CPacket
{
private:
	CHAR*	_Buffer;

public:
	bool Initailize(CHAR* buffer, ULONG size, ULONG* remainderSize);

public:
	CPacket();
	~CPacket();
};

