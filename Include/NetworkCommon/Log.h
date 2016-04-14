#pragma once
#include "NetworkCommon\Singleton.h"
#include "NetworkCommon\Synchronized.h"

#define LOG_BUFFER_SIZE 256

class CLog : public CSingleton<CLog>
{
private:
	CSectionObject	_LogSec;

public:
	void Log(const char * msg, ...);
	void Error(const char * fileName, const char * funcName, int line, const char * msg, ...);

private:
	std::string CurrentDateTime();

public:
	CLog();
	~CLog();
};

#define LOG_MSG(msg, ...) CLog::GetInstance()->Log(msg, __VA_ARGS__);
#define LOG_ERROR_MSG(msg, ...) CLog::GetInstance()->Error(__FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__);
#define LOG_SHUTDOWN CLog::Release();
