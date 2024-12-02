#include "StdAfx.h"
#include "MyController.h"
#include "AftThreadsDlg.h"

enum THREAD_FINISH_STATES
{
	THREAD_FINISH_SUCCESS = 0,	 // ����� �������� �������
	THREAD_FINISH_FORCED,		 // ����� �������� �� �������
	THREAD_FINISH_ERROR = -1	 // ����� �������� � �������
};

UINT MyController::AfxFunction(LPVOID param)
{
	ThreadParams* threadParams = static_cast<ThreadParams*>(param);

	if (threadParams == nullptr || !threadParams->IsDialogValid())
	{
		return THREAD_FINISH_ERROR;
	}

	// ��������� �� ������ ��������� ����� ������� ������
	if (threadParams->IsStopRequested())
	{
		threadParams->NotifyCallback(WM_AFX_THREAD_FORCED_END);
		return THREAD_FINISH_FORCED;
	}

	for (int i = 0; i < 10; i++)
	{
		if (threadParams->IsStopRequested() || !threadParams->IsDialogValid())
		{
			threadParams->NotifyCallback(WM_AFX_THREAD_FORCED_END);
			return THREAD_FINISH_FORCED;
		}

		::SetDlgItemInt(threadParams->dialogHwnd, IDC_TEXT_CHANGE, i + 1, TRUE);

		Sleep(500);
	}

	threadParams->NotifyCallback(WM_AFX_THREAD_END);

	return THREAD_FINISH_SUCCESS;
}