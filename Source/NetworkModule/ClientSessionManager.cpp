#include "NetworkModule/ClientSession.h"
#include "NetworkModule/ClientSessionManager.h"


CClientSessionManager::CClientSessionManager()
	: _NumPostAccept(0)
{
}


CClientSessionManager::~CClientSessionManager()
{

}

void CClientSessionManager::PushClientSession(CClientSession* client)
{
	_ClientSessions.push(client);
	InterlockedExchangeAdd(&_NumPostAccept, 1);
}

CClientSession* CClientSessionManager::GetClientSessions()
{
	return _ClientSessions.front();
}

bool CClientSessionManager::AcceptClientSessions(SOCKET listenSocket, TP_IO* io)
{
	long count = _NumPostAccept;
	for (long i = 0; i < count; ++i)
	{
		StartThreadpoolIo(io);
		_ClientSessions.front()->PostAccept(listenSocket);
		InterlockedDecrement(&_NumPostAccept);
	}

	return true;
}