#include "NetworkModule\IOCompletionPort.h"
#include "NetworkModule\ClientSession.h"
#include "NetworkModule\ClientSessionManager.h"
#include "NetworkModule\Network.h"

CNetwork::CNetwork()
	: _ListenSocket(INVALID_SOCKET)
	, _TPIO(NULL)
	, _IOCompletionPort(NULL)
	, _ClientSessionManager(NULL)
{
}

CNetwork::~CNetwork()
{
	Release();
}

bool CNetwork::Initialize(unsigned short port, CClientSessionManager* clientSessionManager)
{
	_ClientSessionManager = clientSessionManager;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;

	_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (_ListenSocket == INVALID_SOCKET)
		return false;

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (SOCKET_ERROR == bind(_ListenSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)))
		return false;

	_TPIO = CreateThreadpoolIo(reinterpret_cast<HANDLE>(_ListenSocket), CNetwork::IoCompletionCallback, NULL, NULL);
	if (_TPIO == NULL)
		return false;

	StartThreadpoolIo(_TPIO);

	if (SOCKET_ERROR == listen(_ListenSocket, SOMAXCONN))
		return false;

	return true;
}

void CNetwork::Run()
{
	_ClientSessionManager->AcceptClientSessions(_ListenSocket, _TPIO);

	while (true)
	{
		Sleep(1000);
	}
}

void CNetwork::Release()
{
	if (_IOCompletionPort != NULL)
	{
		delete _IOCompletionPort;
		_IOCompletionPort = NULL;
	}

	if (_TPIO != NULL)
	{
		WaitForThreadpoolIoCallbacks(_TPIO, true);
		CloseThreadpoolIo(_TPIO);
		_TPIO = NULL;
	}

	WSACleanup();
}

void CALLBACK CNetwork::IoCompletionCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context,	PVOID Overlapped, 
												ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	if (IoResult != ERROR_SUCCESS)
	{
	}
	else
	{
		OVERLAPPED_BASE* overlapped_Base = (OVERLAPPED_BASE*)Overlapped;

		switch (overlapped_Base->_Mode)
		{
		case OVERLAPPED_ACCEPT:
			overlapped_Base->_Client->AcceptCompletion();
			overlapped_Base->_Client->ZeroByteReceive();
			break;
		case OVERLAPPED_ZERO_READ:
			overlapped_Base->_Client->PostReceive();
			break;
		case OVERLAPPED_READ:
			overlapped_Base->_Client->RecviePacketProcessing(NumberOfBytesTransferred);
			overlapped_Base->_Client->ZeroByteReceive();
			break;
		case OVERLAPPED_WRITE:
			overlapped_Base->_Client->SendCompletion(Overlapped);
			break;
		case OVERLAPPED_DISCONNECT:
			break;
		default:
			break;
		}
	}
}

bool CNetwork::GetLocalAddress(SOCKET socket, std::string& ip, u_short& port)
{
	sockaddr_in6 addr6;
	ZeroMemory(&addr6, sizeof(addr6));
	int size = sizeof(addr6);

	char buff[INET6_ADDRSTRLEN] = { 0, };

	if (0 == getsockname(socket, reinterpret_cast<sockaddr*>(&addr6), &size))
	{
		if (size == sizeof(sockaddr_in6))
		{
			port = ntohs(addr6.sin6_port);
			inet_ntop(AF_INET6, &addr6.sin6_addr, buff, INET6_ADDRSTRLEN);

			ip = buff;
		}
		else if (size == sizeof(sockaddr_in))
		{
			sockaddr_in* pAddr4 = reinterpret_cast<sockaddr_in*>(&addr6);

			port = ntohs(pAddr4->sin_port);
			inet_ntop(AF_INET, &pAddr4->sin_addr, buff, INET_ADDRSTRLEN);

			ip = buff;
		}
		else
		{
			return false;
		}

		return true;
	}

	return false;
}