#include "stdafx.h"
#include "ClientSession.h"


CClientSession::CClientSession()
	: _Socket(INVALID_SOCKET)
{
	memset(&_ClientAddr, 0, sizeof(SOCKADDR_IN));
}


CClientSession::~CClientSession()
{
}

bool CClientSession::PostAccept(SOCKET listenSocket)
{
	DWORD dwSize = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = (CHAR*)m_RecvBuffer;
	WsaBuf.len = MAX_BUFFER_SIZE;

	if (FALSE == AcceptEx( listenSocket
						 , _Socket
					     , &WsaBuf
						 , 0
						 , sizeof(SOCKADDR_IN) + 16
						 , sizeof(SOCKADDR_IN) + 16
						 , &dwSize
						 , (LPOVERLAPPED)acceptContext))
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
	WsaBuf.buf = (CHAR*)m_RecvBuffer;
	WsaBuf.len = MAX_BUFFER_SIZE;

	int result = WSARecv( _Socket
						, &WsaBuf
						, 1
						, &dwSize
						, &dwFlag
						, (LPOVERLAPPED)&m_ReadOverlapped
						, NULL);

	if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		return false;
	}

	return true;
}

bool CClientSession::PostSend(BYTE* pSendBuffer, DWORD dwSendBufferSize)
{
	DWORD dwSize = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = (CHAR*)pSendBuffer;
	WsaBuf.len = dwSendBufferSize;

	int result = WSASend( _Socket
						, &WsaBuf
						, 1
						, &dwSize
						, 0
						, (LPOVERLAPPED)&m_SendOverlapped
						, NULL);

	if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		return false;
	}

	return true;
}