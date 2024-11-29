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
	return manager->m_AfxPtrFunc(manager->m_Param);
}


bool ThreadManager::StartAfxThread()
{
	/*if (m_IsRunning)
	{
		return false;
	}*/

	ResetEvent(m_AfxStopEvent);															// —брасываем событие остановки 
	m_AfxPtrThread = AfxBeginThread((AFX_THREADPROC)AfxThreadWrapper, (LPVOID)this);

	if (m_AfxPtrThread != NULL)
	{
		SetThreadName(m_AfxPtrThread->m_nThreadID, m_ThreadName.c_str());

		//m_IsRunning = true;

		return true;
	}
	else
	{
		return false;
	}
}

void ThreadManager::StopAfxThread()
{
	if (m_AfxPtrThread != NULL)
	{
		SetEvent(m_AfxStopEvent);
		WaitForSingleObject(m_AfxPtrThread->m_hThread, INFINITE);
	}
}