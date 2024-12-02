#pragma once
#include <Windows.h>
#include <string>
#include <functional>

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

	typedef std::function<void()> ThreadCallback; // Тип для обратного вызова
	ThreadCallback m_OnThreadEndCallback;        // Обратный вызов

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
	// Задать имя потока (работает только в режиме Debug)
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

