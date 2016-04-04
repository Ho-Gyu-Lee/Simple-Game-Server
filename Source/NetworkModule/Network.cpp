#include "NetworkModule/IOCompletionPort.h"
#include "NetworkModule\ClientSession.h"
#include "NetworkModule\ClientSessionManager.h"
#include "NetworkModule/Network.h"

CNetwork::CNetwork()
	: _ListenSocket(INVALID_SOCKET)
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

	_IOCompletionPort = new CIOCompletionPort;
	_IOCompletionPort->Initialize();

	_IOCompletionPort->RegisterIoCompletion((HANDLE)_ListenSocket, NULL);

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (SOCKET_ERROR == bind(_ListenSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)))
		return false;

	if (SOCKET_ERROR == listen(_ListenSocket, SOMAXCONN))
		return false;

	return true;
}

void CNetwork::Run()
{
	//_ClientSessionManager->GetClientSessions()->PostAccept(_ListenSocket);

	while (true)
	{
		DWORD		 numberOfByteTransfered = 0;
		ULONG_PTR	 completionKey = NULL;
		LPOVERLAPPED overlapped = NULL;

		_IOCompletionPort->GetIoCompletionStatus(&numberOfByteTransfered, completionKey, overlapped);
	}
}

void CNetwork::Release()
{
	if (_IOCompletionPort != NULL)
	{
		delete _IOCompletionPort;
		_IOCompletionPort = NULL;
	}

	WSACleanup();
}