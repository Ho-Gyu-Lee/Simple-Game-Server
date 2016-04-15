// GameServerSample.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include "NetworkCommon\Log.h"
#include "NetworkCommon\ConcurrentQueue.h"

#include "NetworkModule\Network.h"
#include "NetworkModule\ClientSession.h"
#include "NetworkModule\ClientSessionManager.h"

int main()
{
	CConcurrentQueue<CClientSession*> clientSessionQueue;

	clientSessionQueue.Push(new CClientSession);

	CClientSessionManager* clientSessionManager = new CClientSessionManager;

	for (int i = 0; i < MAX_CONNECTION; ++i)
	{
		clientSessionManager->PushClientSession(new CClientSession);
	}

	CNetwork* network = new CNetwork;
	
	if (false == network->Initialize(20020, clientSessionManager))
	{
		LOG_ERROR_MSG("Failed Server Initialize");
	}

	LOG_MSG("Start Server");
	network->Run();

	LOG_SHUTDOWN;

    return 0;
}