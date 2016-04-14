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

	TP_IO*		_TPIO;

	CHAR _RecvBuffer[MAX_BUFFER_SIZE];
	ULONG _EndBufferIndex;

public:
	void Initailize();
	bool PostAccept(SOCKET listenSocket, TP_IO* io);
	bool AcceptCompletion();
	bool ZeroByteReceive();
	bool PostReceive();
	bool PostSend(CHAR* pSendBuffer, DWORD dwSendBufferSize);
	bool Release();

public:
	void RecviePacketProcessing(ULONG NumberOfBytesTransferred);

public:
	SOCKET GetSocket() { return _Socket; }

public:
	CClientSession();
	~CClientSession();
};