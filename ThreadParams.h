#pragma once
#include <afxwin.h>
#include <functional>

typedef std::function<void(HWND, const int)> CallbackDialogMsg;

struct ThreadParams
{
	HANDLE stopEvent;			// Событие для завершения потока
	HWND dialogHwnd;			// Дескриптор окна диалога
	CallbackDialogMsg callbackDlg;	// Функция для вызова сообщения о том, что поток закончил своё выполнение

    ~ThreadParams()
    {
        if (stopEvent)
        {
            CloseHandle(stopEvent);
        }
    }

    // Метод для проверки, был ли подан сигнал на завершение
    bool IsStopRequested() const
    {
        return WaitForSingleObject(stopEvent, 0) == WAIT_OBJECT_0;
    }

    // Метод для проверки, что дескриптор окна валиден
    bool IsDialogValid() const
    {
        return ::IsWindow(dialogHwnd);
    }

    // Метод для вызова callback, если он установлен
    void NotifyCallback(int message) const
    {
        if (callbackDlg && IsDialogValid())
        {
            callbackDlg(dialogHwnd, message);
        }
    }
};