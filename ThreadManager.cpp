#include "StdAfx.h"
#include "ThreadManager.h"

void ThreadManager::SetThreadName(DWORD dwThreadID, const std::string& threadName)
{
	const int threadExceptionId = 0x406D1388;
	const int dwType = 0x1000;

	THREADNAME_INFO info;
	info.dwType = dwType;
	info.szName = threadName.c_str();
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
	ThreadParams* params = manager->m_Params;

	UINT result = WM_AFX_THREAD_END;

	try
	{
		result = manager->m_AfxPtrFunc(params); // Выполнение логики потока
	}
	catch (const std::exception& ex)
	{
		TRACE("Exception in thread: %s\n", ex.what());
	}

	params->NotifyCallback(result);

	return result;
}

bool ThreadManager::StartAfxThread()
{
	m_AfxPtrThread = AfxBeginThread((AFX_THREADPROC)&ThreadManager::AfxThreadWrapper, this);
	SetThreadName(m_AfxPtrThread->m_nThreadID, m_ThreadName.c_str());
	return m_AfxPtrThread != NULL;
}

void ThreadManager::StopAfxThread()
{
	if (m_AfxPtrThread != nullptr)
	{
		SetEvent(m_Params->stopEvent);

		if (WaitForSingleObject(m_AfxPtrThread->m_hThread, 5000) == WAIT_TIMEOUT)
		{
			TRACE("Thread did not terminate in time: %s\n", m_ThreadName.c_str());
		}

		m_AfxPtrThread = nullptr;
	}
}