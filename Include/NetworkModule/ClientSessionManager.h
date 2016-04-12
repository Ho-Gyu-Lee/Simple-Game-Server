#pragma once
#include "NetworkCommon\Define.h"

class CClientSession;
class CClientSessionManager
{
private:
	std::queue<CClientSession*> _ClientSessions;
	volatile long _NumPostAccept;

public:
	void PushClientSession(CClientSession* client);
	CClientSession* GetClientSessions();
	bool AcceptClientSessions(SOCKET listenSocket, TP_IO* io);

public:
	CClientSessionManager();
	~CClientSessionManager();
};

