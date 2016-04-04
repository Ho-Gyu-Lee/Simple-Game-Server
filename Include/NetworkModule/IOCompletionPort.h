#pragma once
#include "NetworkCommon\Define.h"

class CIOCompletionPort
{
private:
	HANDLE _CompletionPort;

private:
	static unsigned int WINAPI IoWorkerThread(LPVOID lpParam);

public:
	bool Initialize();
	bool RegisterIoCompletion(HANDLE handle, ULONG_PTR completionKey);
	bool PostIoCompletion(LPOVERLAPPED overlapped, ULONG_PTR completionKey);

public:
	CIOCompletionPort();
	~CIOCompletionPort();
};

