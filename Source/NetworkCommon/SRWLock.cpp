#include "NetworkCommon\SRWLock.h"

CSRWLock::CSRWLock()
{
	InitializeSRWLock(&_Sync);
}


CSRWLock::~CSRWLock()
{
}
