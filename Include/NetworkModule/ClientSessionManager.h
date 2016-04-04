#pragma once
#include "NetworkCommon\Define.h"

class CClientSession;
class CClientSessionManager
{
private:
	std::queue<CClientSession*> _ClientSessions;

public:
	CClientSession* GetClientSessions();

public:
	CClientSessionManager();
	~CClientSessionManager();
};

