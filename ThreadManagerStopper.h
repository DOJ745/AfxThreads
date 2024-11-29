#pragma once
#include "ThreadManager.h"
// ����������� ����� � ������� ����������� ������� ��� �������� ���������� ������
class ThreadManagerStopper
{
private:
	ThreadManagerStopper(const ThreadManagerStopper&);            // ������ ������������ �����������
	ThreadManagerStopper& operator=(const ThreadManagerStopper&); // ������ ��������� ������������

protected:
	ThreadManagerStopper() {};

public:
	virtual ~ThreadManagerStopper() {};

public:
	// ���������� ���������� ������ ������ � ������������� ������ ��������� ������� ������
	void StopAfxThreadManager(ThreadManager*& ptrThrMng)
	{
		if (ptrThrMng != NULL)
		{
			ptrThrMng->StopAfxThread();
			DeletePtr(ptrThrMng);
		}
	}

	// ����������: ����� ����������� �������
	// ���������� ���������� ���� ������� ��� ����������� �� ����������� 
	virtual void StopAllThreadManagers() = 0;

private:
	// �������� ��������� �� ��������� ������ �� ������ �� ��� ���������
	void DeletePtr(ThreadManager*& ptrThrMng)
	{
		if (ptrThrMng)
		{
			delete ptrThrMng;
			ptrThrMng = NULL;
		}
	}

};

