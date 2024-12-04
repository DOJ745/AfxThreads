#pragma once
#include "Windows.h"
#include "ThreadManager.h"
#include "UniquePtr.h"
#include "ThreadParams.h"
#include "IThreadMethods.h"
#include <memory>

class MyController : public IThreadMethods
{
private:
	UniquePtr<ThreadManager> m_PtrThreadManager;
	UniquePtr<ThreadManager> m_PtrThreadManagerTwo;
	int m_MyNumber;

public:
	MyController(int myNumber): m_MyNumber(myNumber)
	{
	};

	~MyController() 
	{
		StopThread(m_PtrThreadManager, 10000);
		StopThread(m_PtrThreadManagerTwo, 10000);
	};

	UniquePtr<ThreadManager>& GetThreadManager()
	{
		return m_PtrThreadManager;
	};

	UniquePtr<ThreadManager>& GetThreadManagerTwo() 
	{
		return m_PtrThreadManagerTwo;
	};

	int GetMyNumber() const
	{
		return m_MyNumber;
	}

	void SetMyNumber(int myNumber)
	{
		m_MyNumber = myNumber;
	}

public:
	void StartThread(UniquePtr<ThreadManager>& ptrThreadManager, HWND dlgHwnd, UINT(*threadFunc)(LPVOID), const std::string& threadName) override
	{
		if (!ptrThreadManager.get())
		{
			// Создаём параметры для потока
			ThreadParams* params = new ThreadParams();
			params->dlgHwnd = dlgHwnd;
			params->threadName = threadName;

			// Создаём и запускаем поток
			ptrThreadManager.reset(new ThreadManager(threadFunc, params, threadName));

			ptrThreadManager->StartAfxThread();
		}
	}

	void StopThread(UniquePtr<ThreadManager>& ptrThreadManager, int timeoutMs) override
	{
		if (ptrThreadManager.get())
		{
			ptrThreadManager->StopAfxThread(timeoutMs);
			ResetThreadPtr(ptrThreadManager);
		}
	}

	void ResetThreadPtr(UniquePtr<ThreadManager>& ptrThreadManager)
	{
		ptrThreadManager.reset();
	}

	static UINT AfxFunction(LPVOID param);
	static UINT AfxFunctionTwo(LPVOID param);
};