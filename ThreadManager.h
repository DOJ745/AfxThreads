#pragma once
#include <Windows.h>
#include <string>

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

    typedef UINT(*AfxFunctionPtr)(LPVOID);
    HANDLE m_AfxStopEvent;			// Событие для остановки потока CWinThread*
    CWinThread* m_AfxPtrThread;		// Указатель на ресурс потока
    AfxFunctionPtr m_AfxPtrFunc;	// Указатель на функцию потока
	LPVOID m_Param;                 // Параметр функции потока
	std::string m_ThreadName;		// Имя потока
    bool m_IsRunning;				// Проверка на запуск потока

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
    
    // За очистку памяти и ресурсов отвечает ThreadManagerStopper
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
	// Задать имя потока (работает только в режиме Debug)
	void SetThreadName(DWORD dwThreadID, const char* threadName);


	static UINT AfxThreadWrapper(LPVOID param);
};

