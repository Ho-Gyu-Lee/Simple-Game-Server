#include "NetworkCommon\MiniDumpHelp.h"

CMiniDumpHelp::CMiniDumpHelp()
{
}

CMiniDumpHelp::~CMiniDumpHelp()
{
}

void CMiniDumpHelp::Initailize()
{
	SetUnhandledExceptionFilter(CMiniDumpHelp::ProcessMiniDump);
}

std::wstring CMiniDumpHelp::GetDumpFilename()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

	std::wstring module_path;
	std::wstring dump_filename;

	static WCHAR ModulePath[1024];

	if (::GetModuleFileNameW(0, ModulePath, sizeof(ModulePath) / sizeof(WCHAR)) == 0)
	{
		return std::wstring();
	}

	module_path = ModulePath;
	dump_filename.assign(module_path, 0, module_path.rfind(L"\\") + 1);

	dump_filename = dump_filename + L".dmp";

	return dump_filename;
}

LONG WINAPI CMiniDumpHelp::ProcessMiniDump(__in PEXCEPTION_POINTERS pExceptionPointer)
{
	MINIDUMP_EXCEPTION_INFORMATION MinidumpExceptionInformation;
	std::wstring dump_filename = CMiniDumpHelp::GetDumpFilename();

	MinidumpExceptionInformation.ThreadId = ::GetCurrentThreadId();
	MinidumpExceptionInformation.ExceptionPointers = pExceptionPointer;
	MinidumpExceptionInformation.ClientPointers = FALSE;

	if (dump_filename.empty() == true)
	{
		::TerminateProcess(::GetCurrentProcess(), 0);
	}

	HANDLE hDumpFile = ::CreateFileW( dump_filename.c_str()
									, GENERIC_WRITE
									, FILE_SHARE_WRITE
									, NULL
									, CREATE_ALWAYS
									, FILE_ATTRIBUTE_NORMAL
									, NULL);

	MiniDumpWriteDump( GetCurrentProcess()
					 , GetCurrentProcessId()
					 , hDumpFile
					 , MiniDumpNormal
					 , &MinidumpExceptionInformation
					 , NULL
					 , NULL);

	::TerminateProcess(::GetCurrentProcess(), 0);

	return 0;
}