#include "StdAfx.h"
#include "MyController.h"
#include "AftThreadsDlg.h"

UINT MyController::AfxFunction(LPVOID param)
{
	CAftThreadsDlg* dlg = (CAftThreadsDlg*)param;

	int msSleep = 50;
	int controllerNumber = dlg->m_PtrMyController->GetMyNumber();

	if (dlg->m_PtrMyController->m_PtrThreadManager->IsStopEvent())
	{
		::PostMessageA(dlg->GetSafeHwnd(), WM_AFX_THREAD_FORCED_END, (WPARAM)dlg->GetSafeHwnd(), NULL);
		return 0;
	}
	// Step 1
	for (int i = 0; i < 10; i++)
	{
		if (dlg->m_PtrMyController->m_PtrThreadManager->IsStopEvent())
		{
			::PostMessageA(dlg->GetSafeHwnd(), WM_AFX_THREAD_FORCED_END, (WPARAM)dlg->GetSafeHwnd(), NULL);
			return 0;
		}

		dlg->SetDlgItemInt(IDC_TEXT_CHANGE, i + controllerNumber);
		Sleep(msSleep);
	}

	// Step 2
	for (int i = 0; i < 10; i++)
	{
		if (dlg->m_PtrMyController->m_PtrThreadManager->IsStopEvent())
		{
			::PostMessageA(dlg->GetSafeHwnd(), WM_AFX_THREAD_FORCED_END, (WPARAM)dlg->GetSafeHwnd(), NULL);
			return 0;
		}

		dlg->SetDlgItemInt(IDC_TEXT_CHANGE, i + controllerNumber * 2);
		Sleep(msSleep);
	}
	
	// Step 3
	for (int i = 0; i < 10; i++)
	{
		if (dlg->m_PtrMyController->m_PtrThreadManager->IsStopEvent())
		{
			::PostMessageA(dlg->GetSafeHwnd(), WM_AFX_THREAD_FORCED_END, (WPARAM)dlg->GetSafeHwnd(), NULL);
			return 0;
		}

		dlg->SetDlgItemInt(IDC_TEXT_CHANGE, i + controllerNumber * 3);
		Sleep(msSleep);
	}

	::PostMessageA(dlg->GetSafeHwnd(), WM_AFX_THREAD_END, (WPARAM)dlg->GetSafeHwnd(), NULL);

	return 0;
}