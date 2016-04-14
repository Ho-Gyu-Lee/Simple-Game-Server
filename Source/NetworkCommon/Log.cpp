#include "NetworkCommon\Log.h"
#include "NetworkCommon\Define.h"

CLog::CLog()
{
}


CLog::~CLog()
{
}

void CLog::Trace(const char * msg, ...)
{
	CSynchronized synchronized(&_LogSec);

	static char buffer[LOG_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, msg);
	vsnprintf_s(buffer, LOG_BUFFER_SIZE, LOG_BUFFER_SIZE - 1, msg, args);
	va_end(args);

	std::cout << buffer << std::endl;
}

void CLog::Error(const char * fileName, const char * funcName, int line, const char * msg, ...)
{
	CSynchronized synchronized(&_LogSec);

	static char buffer[LOG_BUFFER_SIZE] = { 0, };
	va_list args;
	va_start(args, msg);
	vsnprintf_s(buffer, LOG_BUFFER_SIZE, LOG_BUFFER_SIZE - 1, msg, args);
	va_end(args);

	std::cout << "File: " << fileName << "\nFunction: " << funcName << "\nLine: " << line \
		<< "\nError: " << buffer << std::endl;
}