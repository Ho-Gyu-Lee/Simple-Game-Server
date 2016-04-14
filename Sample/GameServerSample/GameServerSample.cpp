// GameServerSample.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "NetworkCommon\Log.h"
#include "NetworkModule\Network.h"
#include "NetworkModule\ClientSession.h"
#include "NetworkModule\ClientSessionManager.h"

int main()
{
	CClientSessionManager* clientSessionManager = new CClientSessionManager;

	for (int i = 0; i < MAX_CONNECTION; ++i)
	{
		clientSessionManager->PushClientSession(new CClientSession);
	}

	CLog::GetInstance()->Trace("TEST");
	//TRACE("TEST");

	CNetwork* network = new CNetwork;
	network->Initialize(20020, clientSessionManager);
	network->Run();

    return 0;
}