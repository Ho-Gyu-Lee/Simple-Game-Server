// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#pragma comment(lib,"ws2_32.lib")

#include <winsock2.h>
#include <mswsock.h>
#include <process.h>

#define MAX_BUFFER_SIZE 1024

typedef enum { OVERLAPPED_ACCEPT, OVERLAPPED_READ, OVERLAPPED_WRITE, OVERLAPPED_ERROR } OVERLAP_MODE;

typedef struct OVERLAPPED_BASE
{
	OVERLAPPED		_Overlapped;			// Overlapped ����ü
	OVERLAP_MODE	_Mode;					// Overlapped ��� ( Send, Receive )

} OVERLAPPED_BASE, *LPOVERLAPPED_BASE;