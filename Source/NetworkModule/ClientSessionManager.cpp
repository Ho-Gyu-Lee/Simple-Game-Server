#include "NetworkModule/ClientSession.h"
#include "NetworkModule/ClientSessionManager.h"


CClientSessionManager::CClientSessionManager()
{
}


CClientSessionManager::~CClientSessionManager()
{

}

void CClientSessionManager::PushClientSession(CClientSession* client)
{
	_ClientSessions.push(client);
}

CClientSession* CClientSessionManager::GetClientSessions()
{
	return _ClientSessions.front();
}

bool CClientSessionManager::AcceptClientSessions()
{
	return true;
}