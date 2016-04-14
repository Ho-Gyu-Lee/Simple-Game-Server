#include "NetworkCommon\Log.h"
#include "NetworkCommon\Define.h"

CLog::CLog()
{
}


CLog::~CLog()
{
}

void CLog::Log(const char * msg, ...)
{
	CSynchronized synchronized(&_LogSec);

	static char buffer[LOG_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, msg);
	vsnprintf_s(buffer, LOG_BUFFER_SIZE, LOG_BUFFER_SIZE - 1, msg, args);
	va_end(args);

	std::cout << CurrentDateTime() << " [INFO] " << buffer << std::endl;
}

void CLog::Error(const char * fileName, const char * funcName, int line, const char * msg, ...)
{
	CSynchronized synchronized(&_LogSec);

	static char buffer[LOG_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, msg);
	vsnprintf_s(buffer, LOG_BUFFER_SIZE, LOG_BUFFER_SIZE - 1, msg, args);
	va_end(args);

	std::cout << CurrentDateTime() << " [ERROR] " << "File: " << fileName << "\nFunction: " << funcName << "\nLine: " << line \
		<< "\nError: " << buffer << std::endl;
}

std::string CLog::CurrentDateTime() 
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

	return buf;
}