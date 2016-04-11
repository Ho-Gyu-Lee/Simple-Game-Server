#pragma once
#include "NetworkCommon\Define.h"

class CClientSession;
class CClientSessionManager
{
private:
	std::queue<CClientSession*> _ClientSessions;

public:
	void PushClientSession(CClientSession* client);
	CClientSession* GetClientSessions();
	bool AcceptClientSessions();

public:
	CClientSessionManager();
	~CClientSessionManager();
};

