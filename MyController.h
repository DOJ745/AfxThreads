#pragma once
#include "Windows.h"
#include "ThreadManagerStopper.h"
#include "ThreadManager.h"

class MyController : public ThreadManagerStopper
{
private:
	ThreadManager* m_PtrThreadManager;
	int m_MyNumber;

public:
	MyController(int myNumber): m_PtrThreadManager(NULL)
	, m_MyNumber(myNumber)
	{

	};

	virtual ~MyController() 
	{
		StopAllThreadManagers();
	};

	int GetMyNumber() const
	{
		return m_MyNumber;
	}

	void SetMyNumber(int myNumber)
	{
		m_MyNumber = myNumber;
	}

	void SetPtrThreadManager(ThreadManager* ptrThreadManager)
	{
		m_PtrThreadManager = ptrThreadManager;
	}

	ThreadManager*& GetThreadManager()
	{
		return m_PtrThreadManager;
	}

public:
	// Остановить выполнение всех потоков под управлением их мененджеров
	void StopAllThreadManagers() override
	{
		StopAfxThreadManager(m_PtrThreadManager);
	}

	static UINT AfxFunction(LPVOID param);
};

