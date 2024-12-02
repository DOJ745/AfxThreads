#pragma once
#include "Windows.h"
#include "ThreadManager.h"
#include "UniquePtr.h"
#include "ThreadParams.h"

// ���������� WinApi ��������� ��� ���������� ������� 
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
			// ������ ��������� ��� ������
			ThreadParams* params = new ThreadParams();
			params->dialogHwnd = dialogHwnd;
			params->testValue = 42;
			
			// ������ � ��������� �����
			m_PtrThreadManager.reset(new ThreadManager(&MyController::AfxFunction, params, "MyThread"));

			// ������������� callback ��� ���������� ������
			m_PtrThreadManager->SetOnThreadEndCallback([dialogHwnd, params]() {
				if (::IsWindow(dialogHwnd))
				{
					::PostMessageA(dialogHwnd, WM_AFX_THREAD_END, 0, 0);
				}

				delete params; // ����������� ������ ����� ����������
			});

			m_PtrThreadManager->StartAfxThread();
		}
	}

	void StopThread()
	{
		if (m_PtrThreadManager.get())
		{
			m_PtrThreadManager->StopAfxThread();
			m_PtrThreadManager.reset();		// ����������� ������
		}
	}

	static UINT AfxFunction(LPVOID param);
};

