// GameServerSample.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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