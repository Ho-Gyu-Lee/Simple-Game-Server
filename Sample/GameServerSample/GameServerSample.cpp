// GameServerSample.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "NetworkModule\Network.h"
#include "NetworkModule\ClientSessionManager.h"

int main()
{
	CNetwork* network = new CNetwork;
	network->Initialize(20020, new CClientSessionManager);
	network->Run();

    return 0;
}