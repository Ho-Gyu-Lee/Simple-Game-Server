#pragma once
#include "NetworkCommon\Synchronized.h"
#include "NetworkCommon\Define.h"

template<typename T>
class CConcurrentQueue
{
private:
	std::queue<T>	_QueueData;
	CSectionObject	_QueueSec;

public:
	inline void Push(T value)
	{
		CSynchronized synchronized(&_QueueSec);
		_QueueData.push(value);
	}

	inline T Pop()
	{
		CSynchronized synchronized(&_QueueSec);
		T value = _QueueData.front();
		_QueueData.pop();
		return value;
	}

	inline bool Empty()
	{
		return _QueueData.empty();
	}

	inline int Size()
	{
		return _QueueData.size();
	}

public:
	CConcurrentQueue() {}
	~CConcurrentQueue() {}
};