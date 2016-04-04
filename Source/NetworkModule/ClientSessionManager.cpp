#include "NetworkModule/ClientSession.h"
#include "NetworkModule/ClientSessionManager.h"


CClientSessionManager::CClientSessionManager()
{
}


CClientSessionManager::~CClientSessionManager()
{
}

CClientSession* CClientSessionManager::GetClientSessions()
{
	return _ClientSessions.front();
}