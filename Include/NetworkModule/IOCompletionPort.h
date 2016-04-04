#pragma once
#include "NetworkCommon\Define.h"

class CIOCompletionPort
{
private:
	HANDLE _CompletionPort;

public:
	bool Initialize();
	bool RegisterIoCompletion(HANDLE handle, ULONG_PTR completionKey);
	bool PostIoCompletion(LPOVERLAPPED overlapped, ULONG_PTR completionKey);
	int GetIoCompletionStatus(DWORD* numberOfByteTransfered, ULONG_PTR completionKey, LPOVERLAPPED overlapped);

public:
	CIOCompletionPort();
	~CIOCompletionPort();
};

