#pragma once

template<typename T>
class CSingleton
{
private:
	static T* _Instance;

public:
	static T* GetInstance()
	{
		if (_Instance == NULL)
		{
			_Instance = new T;
		}

		return _Instance;
	}

	static void Release()
	{
		if (_Instance != NULL)
		{
			delete _Instance;
			_Instance = NULL;
		}
	}

public:
	CSingleton();
	~CSingleton();
};

