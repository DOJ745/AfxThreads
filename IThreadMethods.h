#pragma once
#include <Windows.h>
#include <string>

class IThreadMethods
{
private:
	IThreadMethods(const IThreadMethods&);            // Запрет конструктора копирования
	IThreadMethods& operator=(const IThreadMethods&); // Запрет оператора присваивания

protected:
	IThreadMethods() {};

public:
	// ПРИМЕЧАНИЕ: чисто виртуальная функция
	virtual void StartThread(UniquePtr<ThreadManager>& ptrThreadManager, HWND dlgHwnd, UINT(*threadFunc)(LPVOID), const std::string& threadName) = 0;
	virtual void StopThread(UniquePtr<ThreadManager>& ptrThreadManager, int timeoutMs) = 0;

	virtual ~IThreadMethods() {};
};