#pragma once
#include "NetworkCommon\Define.h"
#include "NetworkCommon\ConcurrentQueue.h"

class CClientSession;
class CClientSessionManager
{
private:
	CConcurrentQueue<CClientSession*> _ClientSessions;

public:
	void PushClientSession(CClientSession* client);
	bool AcceptClientSessions(SOCKET listenSocket, TP_IO* io);

public:
	CClientSessionManager();
	~CClientSessionManager();
};

