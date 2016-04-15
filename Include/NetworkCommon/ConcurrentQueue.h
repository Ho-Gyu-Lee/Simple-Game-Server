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

public:
	void Push(T value);
	T Pop();

public:
	CConcurrentQueue() {}
	~CConcurrentQueue() {}
};

