// GameServerSample.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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