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
	bool AcceptClientSessions(SOCKET listenSocket, TP_IO* io);

public:
	CClientSessionManager();
	~CClientSessionManager();
};

