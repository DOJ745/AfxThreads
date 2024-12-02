#include "StdAfx.h"
#include "ThreadManager.h"

void ThreadManager::SetThreadName(DWORD dwThreadID, const char* threadName)
{
	const int threadExceptionId = 0x406D1388;
	const int dwType = 0x1000;
	THREADNAME_INFO info;
	info.dwType = dwType;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException(threadExceptionId, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

UINT ThreadManager::AfxThreadWrapper(LPVOID param)
{
	ThreadManager* manager = static_cast<ThreadManager*>(param);

	try
	{
		return manager->m_AfxPtrFunc(manager->m_Param);
	}
	catch (const std::exception& ex)
	{
		TRACE1("Exception in thread: %s\n", ex.what());
		return 0;
	}
}

bool ThreadManager::StartAfxThread()
{
	ResetEvent(m_AfxStopEvent);
	m_AfxPtrThread = AfxBeginThread((AFX_THREADPROC)&ThreadManager::AfxThreadWrapper, this);
	SetThreadName(m_AfxPtrThread->m_nThreadID, m_ThreadName.c_str());
	return m_AfxPtrThread != NULL;
}

void ThreadManager::StopAfxThread()
{
	if (m_AfxPtrThread)
	{
		SetEvent(m_AfxStopEvent);
		WaitForSingleObject(m_AfxPtrThread->m_hThread, INFINITE);
		NotifyThreadEnd(); // Уведомляем о завершении потока
	}
}