#include "StdAfx.h"
#include "MyController.h"
#include "AftThreadsDlg.h"

enum THREAD_FINISH_STATES
{
	THREAD_FINISH_SUCCESS = 0,	 // Поток завершён успешно
	THREAD_FINISH_FORCED,		 // Поток завершён по сигналу
	THREAD_FINISH_ERROR = -1	 // Поток завершен с ошибкой
};

UINT MyController::AfxFunction(LPVOID param)
{
	bool isCallbackSent = false;

	ThreadParams* threadParams = static_cast<ThreadParams*>(param);

	if (threadParams == nullptr || !threadParams->IsDialogValid())
	{
		return THREAD_FINISH_ERROR;
	}

	// Проверяем на сигнал остановки перед началом работы
	if (threadParams->IsStopRequested())
	{
		threadParams->NotifyCallback(WM_AFX_THREAD_FORCED_END, "TEST MESSAGE FORCE END");
		isCallbackSent = true;
		return THREAD_FINISH_FORCED;
	}

	for (int i = 0; i < 10; i++)
	{
		if (threadParams->IsStopRequested() || !threadParams->IsDialogValid())
		{
			if (!isCallbackSent)
			{
				threadParams->NotifyCallback(WM_AFX_THREAD_FORCED_END, "TEST MESSAGE FORCE END");
				isCallbackSent = true;
			}

			return THREAD_FINISH_FORCED;
		}

		::SetDlgItemInt(threadParams->dlgHwnd, IDC_TEXT_CHANGE, i + 1, TRUE);

		Sleep(500);
	}

	if (!isCallbackSent)
	{
		threadParams->NotifyCallback(WM_AFX_THREAD_END, "TEST MESSAGE END");
		isCallbackSent = true;
	}

	return THREAD_FINISH_SUCCESS;
}

UINT MyController::AfxFunctionTwo(LPVOID param)
{
	ThreadParams* threadParams = static_cast<ThreadParams*>(param);

	if (threadParams == nullptr || !threadParams->IsDialogValid())
	{
		return THREAD_FINISH_ERROR;
	}

	// Проверяем на сигнал остановки перед началом работы
	if (threadParams->IsStopRequested())
	{
		threadParams->NotifyCallback(WM_AFX_THREAD_FORCED_END, "TESTMESSAGE123");
		return THREAD_FINISH_FORCED;
	}

	for (int i = 0; i < 100; i++)
	{
		if (threadParams->IsStopRequested() || !threadParams->IsDialogValid())
		{
			threadParams->NotifyCallback(WM_AFX_THREAD_FORCED_END, "TESTMESSAGE123");
			return THREAD_FINISH_FORCED;
		}

		::SetDlgItemInt(threadParams->dlgHwnd, IDC_TEXT_CHANGE, i + 155, TRUE);

		Sleep(100);
	}

	threadParams->NotifyCallback(WM_AFX_THREAD_END, "TESTMESSAGE123");

	return THREAD_FINISH_SUCCESS;
}