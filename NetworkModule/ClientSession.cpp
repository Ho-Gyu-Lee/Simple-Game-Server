#include "stdafx.h"
#include "ClientSession.h"


CClientSession::CClientSession()
	: _Socket(INVALID_SOCKET)
{
	ZeroMemory(&_ClientAddr, sizeof(SOCKADDR_IN));

	ZeroMemory(&_AcceptOverlapped, sizeof(OVERLAPPED_BASE));
	ZeroMemory(&_ReadOverlapped, sizeof(OVERLAPPED_BASE));
	ZeroMemory(&_SendOverlapped, sizeof(OVERLAPPED_BASE));

	_AcceptOverlapped._Mode = OVERLAPPED_ACCEPT;
	_ReadOverlapped._Mode	= OVERLAPPED_READ;
	_SendOverlapped._Mode	= OVERLAPPED_WRITE;
}

CClientSession::~CClientSession()
{
}

bool CClientSession::PostAccept(SOCKET listenSocket)
{
	DWORD dwSize = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = (CHAR*)_RecvBuffer;
	WsaBuf.len = MAX_BUFFER_SIZE;

	if (FALSE == AcceptEx( listenSocket
						 , _Socket
					     , &WsaBuf
						 , 0
						 , sizeof(SOCKADDR_IN) + 16
						 , sizeof(SOCKADDR_IN) + 16
						 , &dwSize
						 , (LPOVERLAPPED)&_AcceptOverlapped))
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}

	return true;
}

void CClientSession::AcceptCompletion()
{

}

bool CClientSession::PostReceive()
{
	DWORD dwSize = 0;
	DWORD dwFlag = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = (CHAR*)_RecvBuffer;
	WsaBuf.len = MAX_BUFFER_SIZE;

	int result = WSARecv( _Socket
						, &WsaBuf
						, 1
						, &dwSize
						, &dwFlag
						, (LPOVERLAPPED)&_ReadOverlapped
						, NULL);

	if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		return false;
	}

	return true;
}

bool CClientSession::PostSend(CHAR* pSendBuffer, DWORD dwSendBufferSize)
{
	DWORD dwSize = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = pSendBuffer;
	WsaBuf.len = dwSendBufferSize;

	int result = WSASend( _Socket
						, &WsaBuf
						, 1
						, &dwSize
						, 0
						, (LPOVERLAPPED)&_SendOverlapped
						, NULL);

	if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		return false;
	}

	return true;
}