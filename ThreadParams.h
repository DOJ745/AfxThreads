#pragma once
#include <afxwin.h>
#include <functional>

typedef std::function<void(HWND, const int, const std::string&)> CallbackDialogMsg;

struct ThreadParams
{
	std::string threadName;			// ��� ������ (��� ������������)
	HANDLE stopEvent;				// ������� ��� ���������� ������
	HWND dlgHwnd;					// ���������� ���� �������
	CallbackDialogMsg callbackDlg;	// ������� ��� ������ ��������� � ���, ��� ����� �������� ��� ����������

	ThreadParams()
	{
		SetDefaultParams();
	}

    ~ThreadParams()
    {
		TRACE("=== Destroying thread params of %s... ===\n", threadName.c_str());
        
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
    void NotifyCallback(int message, const std::string& text) const
    {
        if (callbackDlg && IsDialogValid())
        {
            callbackDlg(dlgHwnd, message, text);
        }
    }

private:
	void SetDefaultParams()
	{
		callbackDlg = [](HWND dialogWnd, const int msgType, const std::string& text) 
		{ 
			PostMessageA(dialogWnd, msgType, 0, LPARAM(new std::string(text)));
		};

		stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
};