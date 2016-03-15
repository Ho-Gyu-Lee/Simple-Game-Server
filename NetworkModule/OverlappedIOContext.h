#pragma once
class COverlappedIOContext
{
public:
	virtual void Dispatch(DWORD	numberOfByteTransfered) = 0;

public:
	COverlappedIOContext();
	virtual ~COverlappedIOContext();
};

