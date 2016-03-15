// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#pragma comment(lib,"ws2_32.lib")

#include <winsock2.h>
#include <mswsock.h>
#include <process.h>

#define MAX_BUFFER_SIZE 1024

typedef enum { OVERLAPPED_ACCEPT, OVERLAPPED_READ, OVERLAPPED_WRITE, OVERLAPPED_ERROR } OVERLAP_MODE;

typedef struct OVERLAPPED_BASE
{
	OVERLAPPED		_Overlapped;			// Overlapped 구조체
	OVERLAP_MODE	_Mode;					// Overlapped 모드 ( Send, Receive )

} OVERLAPPED_BASE, *LPOVERLAPPED_BASE;