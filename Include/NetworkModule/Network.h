#pragma once

#include "NetworkCommon\Singleton.h"
#include "NetworkCommon\Define.h"

class CClientSessionManager;
class CIOCompletionPort;
class CNetwork : public CSingleton<CNetwork>
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
	static void CALLBACK IoCompletionCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);

public:
	CClientSessionManager* GetClientSessionManager() { return _ClientSessionManager; }

private:
	bool GetLocalAddress(SOCKET socket, std::string& ip, u_short& port);

public:
	CNetwork();
	~CNetwork();
};

