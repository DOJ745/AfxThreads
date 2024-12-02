#pragma once

template <typename T>
class UniquePtr
{
private:
	T* m_Ptr; // ��������� �� ������

public:
	// ����������� ��������� ���������
	explicit UniquePtr(T* ptr = nullptr)
		: m_Ptr(ptr) {}

	// ���������� ����������� ������
	~UniquePtr()
	{
		TRACE("\t=== Deleting unique ptr...\n");
		
		if (m_Ptr != nullptr)
		{
			delete m_Ptr;
		}
	}

	// ������� ����������� ����� private-����������
private:
	UniquePtr(const UniquePtr&);
	UniquePtr& operator=(const UniquePtr&);

public:
	// ��������� �����������
	UniquePtr(UniquePtr& other)
		: m_Ptr(other.m_Ptr)
	{
		other.m_Ptr = nullptr; // �������� ��������
	}

	UniquePtr& operator=(UniquePtr& other)
	{
		if (this != &other)
		{
			delete m_Ptr;			// ����������� ������� ������
			m_Ptr = other.m_Ptr;	// �������� ��������
			other.m_Ptr = nullptr;
		}
		return *this;
	}

	// ������ � �������
	T* operator->() const { return m_Ptr; }
	T& operator*() const { return *m_Ptr; }

	// ���������� ���������� ���������
	T* get() const { return m_Ptr; }

	// ���������� ���������
	void reset(T* ptr = nullptr)
	{
		delete m_Ptr;
		m_Ptr = ptr;
	}
};