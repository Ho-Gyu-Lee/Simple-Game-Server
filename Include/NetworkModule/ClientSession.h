#pragma once
#include "NetworkCommon\Define.h"

class CClientSession
{
private:
	struct SEND_OVERLAPPED : OVERLAPPED_BASE
	{
		CHAR* _SendBuffer;
	};

private:
	SOCKET			_Socket;
	SOCKADDR_IN		_ClientAddr;

	OVERLAPPED_BASE		_ZeroReadOverlapped;
	OVERLAPPED_BASE		_ReadOverlapped;
	OVERLAPPED_BASE		_AcceptOverlapped;
	OVERLAPPED_BASE		_DisconnectOverlapped;

	SEND_OVERLAPPED		_SendOverlapped;

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
	void SendCompletion(PVOID overlapped);
	bool Release();

public:
	void RecviePacketProcessing(ULONG NumberOfBytesTransferred);

public:
	SOCKET GetSocket() { return _Socket; }

public:
	CClientSession();
	~CClientSession();
};