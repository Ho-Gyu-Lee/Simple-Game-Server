#include "NetworkModule/ClientSession.h"
#include "NetworkModule/ClientSessionManager.h"


CClientSessionManager::CClientSessionManager()
{
}


CClientSessionManager::~CClientSessionManager()
{
	while (_ClientSessions.Empty() == false)
	{
		delete _ClientSessions.Pop();
	}
}

void CClientSessionManager::PushClientSession(CClientSession* client)
{
	_ClientSessions.Push(client);
}

bool CClientSessionManager::AcceptClientSessions(SOCKET listenSocket, TP_IO* io)
{
	int count = _ClientSessions.Size();

	if (count <= 0) return true;

	for (int i = 0; i < count; ++i)
	{
		CClientSession* client = _ClientSessions.Pop();

		client->Initailize();
		if (false == client->PostAccept(listenSocket, io))
			_ClientSessions.Push(client);
	}

	return true;
}