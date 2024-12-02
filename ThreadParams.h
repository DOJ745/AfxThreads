#pragma once
#include <afxwin.h>
#include <functional>

typedef std::function<void(HWND, const int)> CallbackDialogMsg;

struct ThreadParams
{
	HANDLE stopEvent;			// ������� ��� ���������� ������
	HWND dialogHwnd;			// ���������� ���� �������
	CallbackDialogMsg callbackDlg;	// ������� ��� ������ ��������� � ���, ��� ����� �������� ��� ����������

    ~ThreadParams()
    {
        if (stopEvent)
        {
            CloseHandle(stopEvent);
        }
    }

    // ����� ��� ��������, ��� �� ����� ������ �� ����������
    bool IsStopRequested() const
    {
        return WaitForSingleObject(stopEvent, 0) == WAIT_OBJECT_0;
    }

    // ����� ��� ��������, ��� ���������� ���� �������
    bool IsDialogValid() const
    {
        return ::IsWindow(dialogHwnd);
    }

    // ����� ��� ������ callback, ���� �� ����������
    void NotifyCallback(int message) const
    {
        if (callbackDlg && IsDialogValid())
        {
            callbackDlg(dialogHwnd, message);
        }
    }
};