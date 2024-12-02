#include "StdAfx.h"
#include "MyController.h"
#include "AftThreadsDlg.h"

UINT MyController::AfxFunction(LPVOID param)
{
	// ����������� �������� � ���������
	ThreadParams* threadParams = static_cast<ThreadParams*>(param);

	// ��������� ������������ ���������
	if (threadParams == nullptr || !::IsWindow(threadParams->dialogHwnd))
	{
		return 1; // ��������� ����� � �������
	}

	// ������ ������ � �����������
	for (int i = 0; i < 10; i++)
	{
		if (!::IsWindow(threadParams->dialogHwnd))
		{
			return 1; // ���� ���� ���������, ��������� �����
		}

		// �������� ����� �������� ����������
		::SetDlgItemInt(threadParams->dialogHwnd, IDC_TEXT_CHANGE, i + threadParams->testValue, TRUE);

		Sleep(500); // ��������� ���������� ��������
	}

	return 0; // ����� �������� �������
}