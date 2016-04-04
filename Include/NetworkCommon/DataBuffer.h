#pragma once
class CDataBuffer
{
private:
	unsigned char* _Buffer;

	int _StartIndex;
	int _Size;
	int _MaxSize;

public:
	void Allocate(int maxSize);
	bool Append(unsigned char* buffer, int size);
	void Pop(int size);
	int GetDataSize();
	unsigned char* GetBuffer();

public:
	CDataBuffer(int maxSize);
	~CDataBuffer();
};

