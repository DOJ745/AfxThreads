#pragma once
#include <Windows.h>
#include <string>

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
    bool m_IsRunning;				// �������� �� ������ ������

public:
    // Default constructor
    ThreadManager(AfxFunctionPtr threadFunction
        , LPVOID param
        , const std::string& threadName): m_AfxPtrFunc(threadFunction)
		, m_Param(param)
		, m_ThreadName(threadName)
        , m_IsRunning(false)
		, m_AfxStopEvent(::CreateEvent(NULL, TRUE, FALSE, NULL))
		, m_AfxPtrThread (NULL)
        
    {
        //m_AfxStopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
        //m_AfxPtrThread = NULL;
    };
    
    // �� ������� ������ � �������� �������� ThreadManagerStopper
    ~ThreadManager()
    {
        TRACE1("=== Destroying ThreadManager with thread name %s... ===\n", m_ThreadName);
 
        CloseHandle(m_AfxStopEvent);
        ClearThreadPtr();
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

public:
	bool StartAfxThread();
	void StopAfxThread();

private:
	// ������ ��� ������ (�������� ������ � ������ Debug)
	void SetThreadName(DWORD dwThreadID, const char* threadName);


	static UINT AfxThreadWrapper(LPVOID param);
};

