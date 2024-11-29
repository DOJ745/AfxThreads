#pragma once
#include "ThreadManager.h"
// Абстрактный класс с базовой реализацией методов для удаления мененджера потока
class ThreadManagerStopper
{
private:
	ThreadManagerStopper(const ThreadManagerStopper&);            // Запрет конструктора копирования
	ThreadManagerStopper& operator=(const ThreadManagerStopper&); // Запрет оператора присваивания

protected:
	ThreadManagerStopper() {};

public:
	virtual ~ThreadManagerStopper() {};

public:
	// Остановить выполнение потока вместе с освобождением памяти указателя данного потока
	void StopAfxThreadManager(ThreadManager*& ptrThrMng)
	{
		if (ptrThrMng != NULL)
		{
			ptrThrMng->StopAfxThread();
			DeletePtr(ptrThrMng);
		}
	}

	// ПРИМЕЧАНИЕ: чисто виртуальная функция
	// Остановить выполнение всех потоков под управлением их мененджеров 
	virtual void StopAllThreadManagers() = 0;

private:
	// Очистить указатель на мененджер потока по ссылке на его указатель
	void DeletePtr(ThreadManager*& ptrThrMng)
	{
		if (ptrThrMng)
		{
			delete ptrThrMng;
			ptrThrMng = NULL;
		}
	}

};

