// GameServerSample.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include "NetworkCommon\Log.h"
#include "NetworkCommon\MiniDumpHelp.h"

#include "NetworkModule\Network.h"
#include "NetworkModule\ClientSession.h"
#include "NetworkModule\ClientSessionManager.h"

int main()
{
	CMiniDumpHelp::GetInstance()->Initailize();

	CClientSessionManager* clientSessionManager = new CClientSessionManager;

	for (int i = 0; i < MAX_CONNECTION; ++i)
	{
		clientSessionManager->PushClientSession(new CClientSession);
	}
	
	if (false == CNetwork::GetInstance()->Initialize(20000, clientSessionManager))
	{
		LOG_ERROR_MSG("Failed Server Initialize");
	}

	LOG_MSG("Start Server");
	CNetwork::GetInstance()->Run();

	LOG_SHUTDOWN;

    return 0;
}