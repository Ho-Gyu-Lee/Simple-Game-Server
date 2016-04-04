#include "NetworkModule/IOCompletionPort.h"
#include "NetworkModule/NetworkSession.h"

CNetworkSession::CNetworkSession()
	: _IOCompletionPort(NULL)
{
}

CNetworkSession::~CNetworkSession()
{
	if (_IOCompletionPort != NULL)
	{
		delete _IOCompletionPort;
		_IOCompletionPort = NULL;
	}
}

bool CNetworkSession::Initialize()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;

	_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (_ListenSocket == INVALID_SOCKET)
		return false;

	_IOCompletionPort = new CIOCompletionPort;
	_IOCompletionPort->Initialize();

	_IOCompletionPort->RegisterIoCompletion((HANDLE)_ListenSocket, NULL);

	return true;
}