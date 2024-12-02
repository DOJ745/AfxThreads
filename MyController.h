#pragma once
#include "Windows.h"
#include "ThreadManager.h"
#include "UniquePtr.h"
#include "ThreadParams.h"
#include <memory>

class MyController
{
private:
	UniquePtr<ThreadManager> m_PtrThreadManager;
	int m_MyNumber;

public:
	MyController(int myNumber): m_MyNumber(myNumber)
	{
	};

	~MyController() 
	{
		StopThread();
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
	void StartThread(HWND dialogHwnd)
	{
		if (!m_PtrThreadManager.get())
		{
			// Лямбда-выражение для обратного вызова 
			CallbackDialogMsg callbackDlg = [](HWND dialogWnd, const int msgType) 
			{ 
				PostMessageA(dialogWnd, msgType, 0, 0);
			};

			// Создаём параметры для потока
			ThreadParams* params = new ThreadParams();
			params->dialogHwnd = dialogHwnd;
			params->callbackDlg = callbackDlg;

			params->stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

			// Создаём и запускаем поток
			m_PtrThreadManager.reset(new ThreadManager(AfxFunction, params, "MyThread"));

			m_PtrThreadManager->StartAfxThread();
		}
	}

	void StopThread()
	{
		if (m_PtrThreadManager.get())
		{
			m_PtrThreadManager->StopAfxThread();
			ResetThreadPtr();
		}
	}

	void ResetThreadPtr()
	{
		m_PtrThreadManager.reset();
	}

	static UINT AfxFunction(LPVOID param);
};