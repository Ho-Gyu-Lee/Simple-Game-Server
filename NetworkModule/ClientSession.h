#pragma once
class CClientSession
{
private:
	SOCKET			_Socket;
	SOCKADDR_IN		_ClientAddr;

public:
	bool PostAccept(SOCKET listenSocket);
	void AcceptCompletion();
	bool PostReceive();
	bool PostSend(BYTE* pSendBuffer, DWORD dwSendBufferSize);

public:
	CClientSession();
	~CClientSession();
};

