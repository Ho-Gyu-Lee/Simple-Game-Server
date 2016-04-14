#pragma once
#include "NetworkCommon\Define.h"
#include <winsock2.h>
#include <mswsock.h>
#include <Ws2tcpip.h>

class CClientSessionManager;
class CIOCompletionPort;
class CNetwork
{
private:
	SOCKET				   _ListenSocket;
	CIOCompletionPort*	   _IOCompletionPort;
	CClientSessionManager* _ClientSessionManager;

	TP_IO* _TPIO;

public:
	bool Initialize(unsigned short port, CClientSessionManager* clientSessionManager);
	void Run();
	void Release();

public:
	static void CALLBACK IoCompletionCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);

private:
	bool GetLocalAddress(SOCKET socket, std::string& ip, u_short& port);

public:
	CNetwork();
	~CNetwork();
};

