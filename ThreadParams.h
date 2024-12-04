#pragma once
#include <afxwin.h>
#include <functional>

typedef std::function<void(HWND, const int, const std::string&)> CallbackDialogMsg;

struct ThreadParams
{
	std::string threadName;
	HANDLE stopEvent;				// ������� ��� ���������� ������
	HWND dlgHwnd;					// ���������� ���� �������
	CallbackDialogMsg callbackDlg;	// ������� ��� ������ ��������� � ���, ��� ����� �������� ��� ����������

	ThreadParams()
	{
		SetDefaultParams();
	}

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
        return ::IsWindow(dlgHwnd);
    }

    // ����� ��� ������ callback, ���� �� ����������
    void NotifyCallback(int message) const
    {
        if (callbackDlg && IsDialogValid())
        {
            callbackDlg(dlgHwnd, message, threadName);
        }
    }

private:
	void SetDefaultParams()
	{
		callbackDlg = [](HWND dialogWnd, const int msgType, const std::string& threadName) 
		{ 
			// TODO: memory leak
			std::string* pThreadName = new std::string(threadName);
			PostMessageA(dialogWnd, msgType, 0, reinterpret_cast<LPARAM>(pThreadName));
		};

		stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
};