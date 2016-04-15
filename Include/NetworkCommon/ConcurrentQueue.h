#pragma once
#include "NetworkCommon\Synchronized.h"
#include "NetworkCommon\Define.h"

template<typename T>
class CConcurrentQueue
{
private:
	std::queue<T>	_QueueData;
	CSectionObject	_PushSec;
	CSectionObject	_PopSec;

	DWORD _Size;

public:
	void Push(T value)
	{
		CSynchronized synchronized(&_PushSec);
		_QueueData.push(value);
		InterlockedExchangeAdd(&_Size, 1);
	}

	T Pop()
	{
		CSynchronized synchronized(&_PopSec);
		InterlockedDecrement(&_Size);
		return _QueueData.pop();
	}

public:
	CConcurrentQueue(): _Size(0) {}
	~CConcurrentQueue() {}
};