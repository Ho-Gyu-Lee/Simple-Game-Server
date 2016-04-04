#pragma once
#include "NetworkCommon\Define.h"

class CClientSession
{
private:
	SOCKET			_Socket;
	SOCKADDR_IN		_ClientAddr;

	OVERLAPPED_BASE		_ZeroReadOverlapped;
	OVERLAPPED_BASE		_ReadOverlapped;
	OVERLAPPED_BASE		_SendOverlapped;
	OVERLAPPED_BASE		_AcceptOverlapped;
	OVERLAPPED_BASE		_DisconnectOverlapped;

	CHAR _RecvBuffer[MAX_BUFFER_SIZE];

public:
	void Initailize();
	bool PostAccept(SOCKET listenSocket);
	bool AcceptCompletion();
	bool ZeroByteReceive();
	bool PostReceive();
	bool PostSend(CHAR* pSendBuffer, DWORD dwSendBufferSize);
	bool Release();

public:
	CClientSession();
	~CClientSession();
};