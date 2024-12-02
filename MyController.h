#pragma once
#include "Windows.h"
#include "ThreadManager.h"
#include "UniquePtr.h"
#include "ThreadParams.h"

// Уникальные WinApi сообщения для завершения потоков 
enum ThreadMessages
{
	WM_AFX_THREAD_END = WM_USER + 1,
	WM_AFX_THREAD_FORCED_END
};

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
			// Создаём параметры для потока
			ThreadParams* params = new ThreadParams();
			params->dialogHwnd = dialogHwnd;
			params->testValue = 42;
			
			// Создаём и запускаем поток
			m_PtrThreadManager.reset(new ThreadManager(&MyController::AfxFunction, params, "MyThread"));

			// Устанавливаем callback для завершения потока
			m_PtrThreadManager->SetOnThreadEndCallback([dialogHwnd, params]() {
				if (::IsWindow(dialogHwnd))
				{
					::PostMessageA(dialogHwnd, WM_AFX_THREAD_END, 0, 0);
				}

				delete params; // Освобождаем память после завершения
			});

			m_PtrThreadManager->StartAfxThread();
		}
	}

	void StopThread()
	{
		if (m_PtrThreadManager.get())
		{
			m_PtrThreadManager->StopAfxThread();
			m_PtrThreadManager.reset();		// Освобождаем объект
		}
	}

	static UINT AfxFunction(LPVOID param);
};

