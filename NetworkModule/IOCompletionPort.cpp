#include "stdafx.h"
#include "IOCompletionPort.h"

CIOCompletionPort::CIOCompletionPort()
	: _CompletionPort(NULL)
{
}


CIOCompletionPort::~CIOCompletionPort()
{
}

bool CIOCompletionPort::Initialize()
{
	_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (_CompletionPort == NULL)
		return false;

	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	for (DWORD i = 0; i < systemInfo.dwNumberOfProcessors * 2 + 1; i++)
	{
		unsigned int threadID = 0;
		HANDLE workerThread = (HANDLE)_beginthreadex(NULL, 0, IoWorkerThread, _CompletionPort, 0, &threadID);
	}

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

unsigned int WINAPI CIOCompletionPort::IoWorkerThread(LPVOID param)
{
	int			 result = 0;
	DWORD		 numberOfByteTransfered = 0;
	ULONG_PTR	 completionKey = NULL;
	LPOVERLAPPED overlapped = NULL;
	HANDLE		 iocpHandle = (HANDLE)param;

	while (true)
	{
		result = GetQueuedCompletionStatus( iocpHandle
										  , &numberOfByteTransfered
										  , (PULONG_PTR)&completionKey
										  , &overlapped
										  , INFINITE);
	}

	return result;
}