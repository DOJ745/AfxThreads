#pragma once
#include <Windows.h>
#include <string>
#include "ThreadParams.h"

// ���������� WinApi ��������� ��� ���������� ������� 
enum ThreadMessages
{
	WM_AFX_THREAD_END = WM_USER + 1,
	WM_AFX_THREAD_FORCED_END,
	WM_AFX_THREAD_ERROR_END
};

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

    CWinThread* m_AfxPtrThread;				// ��������� �� ������ ������
    typedef UINT(*AfxFunctionPtr)(LPVOID);
	AfxFunctionPtr m_AfxPtrFunc;			// ��������� �� ������� ������
	ThreadParams* m_Params;                 // �������� ������� ������
	std::string m_ThreadName;				// ��� ������

public:
    // Default constructor
    ThreadManager(AfxFunctionPtr threadFunction
        , ThreadParams* params
        , const std::string& threadName): m_AfxPtrFunc(threadFunction)
		, m_Params(params)
		, m_ThreadName(threadName)
		, m_AfxPtrThread(NULL)
    {
    };
    
    ~ThreadManager()
    {
        TRACE("=== Destroying ThreadManager of thread %s ===\n", m_ThreadName.c_str());

		StopAfxThread(10000);
        delete m_Params;
        m_Params = nullptr;
    };

    bool IsThreadHandleEmpty() const
    {
		return m_AfxPtrThread == nullptr;
    }

public:
	bool StartAfxThread();
	void StopAfxThread(int timeoutMs);

private:
	// ������ ��� ������ (�������� ������ � ������ Debug)
	void SetThreadName(DWORD dwThreadID, const std::string& threadName);

	static UINT AfxThreadWrapper(LPVOID param);
};

