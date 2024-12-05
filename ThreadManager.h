#pragma once
#include <Windows.h>
#include <string>
#include "ThreadParams.h"

// Уникальные WinApi сообщения для завершения потоков 
enum ThreadMessages
{
	WM_AFX_THREAD_END = WM_USER + 1,
	WM_AFX_THREAD_FORCED_END,
	WM_AFX_THREAD_ERROR_END
};

class ThreadManager
{
private:
	// Структура для задания имени потока
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType;       // Всегда 0x1000
		LPCSTR szName;      // Имя потока
		DWORD dwThreadID;   // ID потока (получаем при создании через CreateHandle)
		DWORD dwFlags;      // Резерв (всегда 0)
	} THREADNAME_INFO;

    CWinThread* m_AfxPtrThread;				// Указатель на ресурс потока
    typedef UINT(*AfxFunctionPtr)(LPVOID);
	AfxFunctionPtr m_AfxPtrFunc;			// Указатель на функцию потока
	ThreadParams* m_Params;                 // Параметр функции потока
	std::string m_ThreadName;				// Имя потока

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
	// Задать имя потока (работает только в режиме Debug)
	void SetThreadName(DWORD dwThreadID, const std::string& threadName);

	static UINT AfxThreadWrapper(LPVOID param);
};

