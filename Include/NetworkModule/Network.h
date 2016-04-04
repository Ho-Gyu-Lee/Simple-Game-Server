#pragma once
#include "NetworkCommon\Define.h"

class CClientSessionManager;
class CIOCompletionPort;
class CNetwork
{
private:
	SOCKET				   _ListenSocket;
	CIOCompletionPort*	   _IOCompletionPort;
	CClientSessionManager* _ClientSessionManager;

public:
	bool Initialize(unsigned short port, CClientSessionManager* clientSessionManager);
	void Run();
	void Release();

public:
	CNetwork();
	~CNetwork();
};

