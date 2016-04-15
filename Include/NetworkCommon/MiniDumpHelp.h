#pragma once
#include "NetworkCommon\Define.h"
#include "NetworkCommon\Singleton.h"
#include <DbgHelp.h>

class CMiniDumpHelp : public CSingleton<CMiniDumpHelp>
{
public:
	void Initailize();

private:
	static LONG WINAPI ProcessMiniDump(__in PEXCEPTION_POINTERS pExceptionPointer);
	static std::wstring GetDumpFilename();

public:
	CMiniDumpHelp();
	~CMiniDumpHelp();
};

