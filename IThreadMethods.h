#pragma once
#include <Windows.h>
#include <string>

class IThreadMethods
{
private:
	IThreadMethods(const IThreadMethods&);            // ������ ������������ �����������
	IThreadMethods& operator=(const IThreadMethods&); // ������ ��������� ������������

protected:
	IThreadMethods() {};

public:
	// ����������: ����� ����������� �������
	virtual void StartThread(UniquePtr<ThreadManager>& ptrThreadManager, HWND dlgHwnd, UINT(*threadFunc)(LPVOID), const std::string& threadName) = 0;
	virtual void StopThread(UniquePtr<ThreadManager>& ptrThreadManager, int timeoutMs) = 0;

	virtual ~IThreadMethods() {};
};