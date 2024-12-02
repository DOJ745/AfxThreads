#pragma once
#include <afxwin.h>

struct ThreadParams
{
	HWND dialogHwnd; // Дескриптор окна диалога
	int testValue;   // Дополнительные данные, если нужно
};