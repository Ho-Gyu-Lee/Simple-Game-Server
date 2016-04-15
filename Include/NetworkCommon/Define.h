#pragma once

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")
#pragma comment(lib,"DbgHelp.Lib")

#include <winsock2.h>
#include <mswsock.h>
#include <process.h>
#include <queue>
#include <iostream>
#include <string>
#include <time.h>
#include <Ws2tcpip.h>

#define MAX_CONNECTION	10000
#define MAX_BUFFER_SIZE 1024

typedef enum { OVERLAPPED_ACCEPT, OVERLAPPED_ZERO_READ, OVERLAPPED_READ, OVERLAPPED_WRITE, OVERLAPPED_DISCONNECT, OVERLAPPED_ERROR } OVERLAP_MODE;

class CClientSession;
typedef struct OVERLAPPED_BASE
{
	OVERLAPPED		_Overlapped;			// Overlapped 구조체
	OVERLAP_MODE	_Mode;					// Overlapped 모드
	CClientSession* _Client;

} OVERLAPPED_BASE, *LPOVERLAPPED_BASE;