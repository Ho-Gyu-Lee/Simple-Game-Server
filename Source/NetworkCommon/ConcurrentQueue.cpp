#include "NetworkCommon\ConcurrentQueue.h"

template<typename T>
void CConcurrentQueue<T>::Push(T value)
{
	CSynchronized synchronized(&_PushSec);
	_QueueData.push(value);
}

template<typename T>
T CConcurrentQueue<T>::Pop()
{
	CSynchronized synchronized(&_PopSec);
	return _QueueData.pop();
}