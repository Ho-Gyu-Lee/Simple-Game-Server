#pragma once
#include "NetworkCommon\Define.h"

class CSRWLock
{
private:
	SRWLOCK _Sync;

public:
	inline void ReadEnter()
	{
		AcquireSRWLockShared(&_Sync);
	}

	inline void ReadLeave()
	{
		ReleaseSRWLockShared(&_Sync);
	}

	inline void WriteEnter()
	{
		AcquireSRWLockExclusive(&_Sync);
	}

	inline void WriteLeave()
	{
		ReleaseSRWLockExclusive(&_Sync);
	}

public:
	CSRWLock();
	~CSRWLock();
};

