#include "StdAfx.h"
#include "MyController.h"
#include "AftThreadsDlg.h"

UINT MyController::AfxFunction(LPVOID param)
{
	// Преобразуем параметр в структуру
	ThreadParams* threadParams = static_cast<ThreadParams*>(param);

	// Проверяем корректность указателя
	if (threadParams == nullptr || !::IsWindow(threadParams->dialogHwnd))
	{
		return 1; // Завершаем поток с ошибкой
	}

	// Пример работы с интерфейсом
	for (int i = 0; i < 10; i++)
	{
		if (!::IsWindow(threadParams->dialogHwnd))
		{
			return 1; // Если окно закрылось, завершаем поток
		}

		// Изменяем текст элемента интерфейса
		::SetDlgItemInt(threadParams->dialogHwnd, IDC_TEXT_CHANGE, i + threadParams->testValue, TRUE);

		Sleep(500); // Имитируем длительную операцию
	}

	return 0; // Поток завершён успешно
}