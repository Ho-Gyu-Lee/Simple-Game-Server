#include "NetworkModule/Network.h"
#include "NetworkModule/Packet.h"
#include "NetworkModule/ClientSession.h"

CClientSession::CClientSession()
	: _Socket(INVALID_SOCKET)
	, _TPIO(NULL)
	, _EndBufferIndex(0)
{

}

CClientSession::~CClientSession()
{
}

void CClientSession::Initailize()
{
	ZeroMemory(&_ClientAddr, sizeof(SOCKADDR_IN));

	ZeroMemory(&_AcceptOverlapped,	   sizeof(OVERLAPPED_BASE));
	ZeroMemory(&_ZeroReadOverlapped,   sizeof(OVERLAPPED_BASE));
	ZeroMemory(&_ReadOverlapped,	   sizeof(OVERLAPPED_BASE));
	ZeroMemory(&_DisconnectOverlapped, sizeof(OVERLAPPED_BASE));

	_AcceptOverlapped._Client	  = this;
	_ZeroReadOverlapped._Client   = this;
	_ReadOverlapped._Client		  = this;
	_DisconnectOverlapped._Client = this;

	_AcceptOverlapped._Mode		= OVERLAPPED_ACCEPT;
	_ZeroReadOverlapped._Mode	= OVERLAPPED_ZERO_READ;
	_ReadOverlapped._Mode		= OVERLAPPED_READ;
	_DisconnectOverlapped._Mode = OVERLAPPED_DISCONNECT;

	_Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (_Socket == INVALID_SOCKET)
	{
		// Log
	}
}

void CClientSession::RecviePacketProcessing(ULONG NumberOfBytesTransferred)
{
	PostSend(_RecvBuffer, NumberOfBytesTransferred);
	/*
	LONG packetSize = NumberOfBytesTransferred;
	while (true)
	{
		CHAR* sendBuffer = new CHAR[8];
		CopyMemory(sendBuffer, &_RecvBuffer[_EndBufferIndex], 8);

		PostSend(sendBuffer, 8);

		_EndBufferIndex += 8;
		packetSize		-= 8;

		if (packetSize < 0)
		{
			_EndBufferIndex -= 8;
			packetSize += 8;
			break;
		}
	}
	 
	MoveMemory( _RecvBuffer
			  , &_RecvBuffer[_EndBufferIndex]
			  , MAX_BUFFER_SIZE - _EndBufferIndex);

	_EndBufferIndex = packetSize;*/
}

bool CClientSession::PostAccept(SOCKET listenSocket, TP_IO* io)
{
	DWORD dwSize = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = NULL;
	WsaBuf.len = 0;

	StartThreadpoolIo(io);
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

bool CClientSession::AcceptCompletion()
{
	int opt = 0;
	if (SOCKET_ERROR == setsockopt(_Socket, SOL_SOCKET, SO_RCVBUF, (const char*)&opt, sizeof(int)))
	{
		return false;
	}

	opt = 1;
	if (SOCKET_ERROR == setsockopt(_Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int)))
	{
		return false;
	}

	_TPIO = CreateThreadpoolIo(reinterpret_cast<HANDLE>(_Socket), CNetwork::IoCompletionCallback, NULL, NULL);
	if (_TPIO == NULL)
	{
		return false;
	}

	return true;
}

// Non-Paged Pool
bool CClientSession::ZeroByteReceive()
{
	DWORD dwSize = 0;
	DWORD dwFlag = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = NULL;
	WsaBuf.len = 0;

	StartThreadpoolIo(_TPIO);
	int result = WSARecv( _Socket
						, &WsaBuf
						, 1
						, &dwSize
						, &dwFlag
						, (LPOVERLAPPED)&_ZeroReadOverlapped
						, NULL);

	if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		return false;
	}

	return true;
}

bool CClientSession::PostReceive()
{
	DWORD dwSize = 0;
	DWORD dwFlag = 0;

	WSABUF	WsaBuf;
	WsaBuf.buf = &_RecvBuffer[_EndBufferIndex];
	WsaBuf.len = MAX_BUFFER_SIZE - _EndBufferIndex;

	StartThreadpoolIo(_TPIO);
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

	SEND_OVERLAPPED* sendOverlapped = new SEND_OVERLAPPED;
	ZeroMemory(sendOverlapped, sizeof(SEND_OVERLAPPED));

	sendOverlapped->_Client = this;
	sendOverlapped->_Mode = OVERLAPPED_WRITE;
	sendOverlapped->_SendBuffer = pSendBuffer;

	StartThreadpoolIo(_TPIO);
	int result = WSASend( _Socket
						, &WsaBuf
						, 1
						, &dwSize
						, 0
						, (LPOVERLAPPED)sendOverlapped
						, NULL);

	if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		return false;
	}

	return true;
}

void CClientSession::SendCompletion(PVOID overlapped)
{
	SEND_OVERLAPPED* sendOverlapped = (SEND_OVERLAPPED*)overlapped;
	//delete sendOverlapped->_SendBuffer;
	delete sendOverlapped;
}

bool CClientSession::Release()
{
	bool result = TransmitFile(_Socket, NULL, NULL, NULL, (LPOVERLAPPED)&_DisconnectOverlapped, NULL, TF_DISCONNECT | TF_REUSE_SOCKET);

	if (result == false)
	{
		closesocket(_Socket);
		return false;
	}

	if (_TPIO != NULL)
	{
		WaitForThreadpoolIoCallbacks(_TPIO, true);
		CloseThreadpoolIo(_TPIO);
		_TPIO = NULL;
	}

	return true;
}