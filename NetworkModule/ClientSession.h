#pragma once
class CClientSession
{
private:
	SOCKET			_Socket;
	SOCKADDR_IN		_ClientAddr;

	OVERLAPPED_BASE		_ReadOverlapped;
	OVERLAPPED_BASE		_SendOverlapped;
	OVERLAPPED_BASE		_AcceptOverlapped;

	CHAR _RecvBuffer[MAX_BUFFER_SIZE];

public:
	bool PostAccept(SOCKET listenSocket);
	void AcceptCompletion();
	bool PostReceive();
	bool PostSend(CHAR* pSendBuffer, DWORD dwSendBufferSize);

public:
	CClientSession();
	~CClientSession();
};