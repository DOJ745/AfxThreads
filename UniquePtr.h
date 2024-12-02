#pragma once

template <typename T>
class UniquePtr
{
private:
	T* m_Ptr; // Указатель на объект

public:
	// Конструктор принимает указатель
	explicit UniquePtr(T* ptr = nullptr)
		: m_Ptr(ptr) {}

	// Деструктор освобождает память
	~UniquePtr()
	{
		TRACE("\t=== Deleting unique ptr...\n");
		
		if (m_Ptr != nullptr)
		{
			delete m_Ptr;
		}
	}

	// Удаляем копирование через private-декларацию
private:
	UniquePtr(const UniquePtr&);
	UniquePtr& operator=(const UniquePtr&);

public:
	// Реализуем перемещение
	UniquePtr(UniquePtr& other)
		: m_Ptr(other.m_Ptr)
	{
		other.m_Ptr = nullptr; // Забираем владение
	}

	UniquePtr& operator=(UniquePtr& other)
	{
		if (this != &other)
		{
			delete m_Ptr;			// Освобождаем текущий объект
			m_Ptr = other.m_Ptr;	// Забираем владение
			other.m_Ptr = nullptr;
		}
		return *this;
	}

	// Доступ к объекту
	T* operator->() const { return m_Ptr; }
	T& operator*() const { return *m_Ptr; }

	// Возвращает внутренний указатель
	T* get() const { return m_Ptr; }

	// Сбрасывает указатель
	void reset(T* ptr = nullptr)
	{
		delete m_Ptr;
		m_Ptr = ptr;
	}
};