#include "NetworkCommon\Synchronized.h"

CSynchronized::CSynchronized(CSectionObject* sectionObject)
{
	_SecionObject = sectionObject;
	_SecionObject->Enter();
}

CSynchronized::~CSynchronized()
{
	_SecionObject->Leave();
}
