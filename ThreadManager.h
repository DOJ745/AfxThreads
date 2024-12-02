#pragma once
#include <Windows.h>
#include <string>
#include <functional>

class ThreadManager
{
private:
	// ��������� ��� ������� ����� ������
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType;       // ������ 0x1000
		LPCSTR szName;      // ��� ������
		DWORD dwThreadID;   // ID ������ (�������� ��� �������� ����� CreateHandle)
		DWORD dwFlags;      // ������ (������ 0)
	} THREADNAME_INFO;

    typedef UINT(*AfxFunctionPtr)(LPVOID);
    HANDLE m_AfxStopEvent;			// ������� ��� ��������� ������ CWinThread*
    CWinThread* m_AfxPtrThread;		// ��������� �� ������ ������
    AfxFunctionPtr m_AfxPtrFunc;	// ��������� �� ������� ������
	LPVOID m_Param;                 // �������� ������� ������
	std::string m_ThreadName;		// ��� ������

	typedef std::function<void()> ThreadCallback; // ��� ��� ��������� ������
	ThreadCallback m_OnThreadEndCallback;        // �������� �����

public:
    // Default constructor
    ThreadManager(AfxFunctionPtr threadFunction
        , LPVOID param
        , const std::string& threadName): m_AfxPtrFunc(threadFunction)
		, m_Param(param)
		, m_ThreadName(threadName)
		, m_AfxStopEvent(::CreateEvent(NULL, TRUE, FALSE, NULL))
		, m_AfxPtrThread (NULL)
        
    {
        //m_AfxStopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
        //m_AfxPtrThread = NULL;
    };
    
    ~ThreadManager()
    {
        TRACE1("=== ~ThreadManager with thread %s ===\n", m_ThreadName.c_str());

		StopAfxThread();
		::CloseHandle(m_AfxStopEvent);
    };

    bool IsStopEvent() const 
    { 
        return WaitForSingleObject(m_AfxStopEvent, 0) == WAIT_OBJECT_0;
    }

    bool IsThreadHandleEmpty()
    {
        return m_AfxPtrThread != NULL;
    }

    void ClearThreadPtr()
    {
        m_AfxPtrThread = NULL;
    }

	void ThreadManager::SetOnThreadEndCallback(const ThreadCallback& callback)
	{
		m_OnThreadEndCallback = callback;
	}

public:
	bool StartAfxThread();
	void StopAfxThread();

private:
	// ������ ��� ������ (�������� ������ � ������ Debug)
	void SetThreadName(DWORD dwThreadID, const char* threadName);
	static UINT AfxThreadWrapper(LPVOID param);

	void NotifyThreadEnd()
	{
		if (m_OnThreadEndCallback)
		{
			m_OnThreadEndCallback();
		}
	}
};

