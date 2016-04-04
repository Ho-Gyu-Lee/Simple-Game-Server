#pragma once
#include "NetworkCommon\Define.h"

class CIOCompletionPort;
class CNetworkSession
{
private:
	SOCKET				_ListenSocket;
	CIOCompletionPort*  _IOCompletionPort;

public:
	bool Initialize();

public:
	CNetworkSession();
	~CNetworkSession();
};

