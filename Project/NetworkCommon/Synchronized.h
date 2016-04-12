#pragma once
#include "NetworkCommon\Define.h"

class CSectionObject
{
private:
	CRITICAL_SECTION _Sync;

public:
	inline void Enter()
	{
		EnterCriticalSection(&_Sync);
	}

	inline void Leave()
	{
		LeaveCriticalSection(&_Sync);
	}

public:
	CSectionObject()
	{
		InitializeCriticalSectionAndSpinCount(&_Sync, 4000);
	}

	~CSectionObject()
	{
		DeleteCriticalSection(&_Sync);
	}
};

class CSynchronized
{
private:
	CSectionObject*	_SecionObject;

public:
	CSynchronized(CSectionObject* sectionObject);
	~CSynchronized();
};

