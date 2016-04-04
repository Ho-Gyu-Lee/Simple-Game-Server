#include "NetworkModule/IOCompletionPort.h"

CIOCompletionPort::CIOCompletionPort()
	: _CompletionPort(NULL)
{
}


CIOCompletionPort::~CIOCompletionPort()
{
	CloseHandle(_CompletionPort);
}

bool CIOCompletionPort::Initialize()
{
	_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (_CompletionPort == NULL)
		return false;

	return false;
}

bool CIOCompletionPort::RegisterIoCompletion(HANDLE handle, ULONG_PTR completionKey)
{
	if (handle == NULL || completionKey == NULL)
		return false;

	HANDLE resultHandle = CreateIoCompletionPort(handle, _CompletionPort, completionKey, 0);
	if (resultHandle == NULL)
		return false;

	return true;
}

bool CIOCompletionPort::PostIoCompletion(LPOVERLAPPED overlapped, ULONG_PTR completionKey)
{
	if (FALSE == PostQueuedCompletionStatus(_CompletionPort, 0, completionKey, overlapped))
		return false;

	return true;
}

int CIOCompletionPort::GetIoCompletionStatus(DWORD* numberOfByteTransfered, ULONG_PTR completionKey, LPOVERLAPPED overlapped)
{
	return GetQueuedCompletionStatus(_CompletionPort, numberOfByteTransfered, (PULONG_PTR)&completionKey, &overlapped, INFINITE);
}