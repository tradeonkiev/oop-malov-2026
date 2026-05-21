#pragma once

#include "MyIterator.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename T>
class MyArray
{
public:
	using Iterator = MyIterator<T>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstIterator = MyIterator<const T>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	MyArray() noexcept
		: m_data(nullptr)
		, m_size(0)
		, m_capacity(0)
	{
	}

	MyArray(const MyArray& other) noexcept
		: m_data(nullptr)
		, m_size(0)
		, m_capacity(0)
	{
		CopyFrom(other);
	}

	MyArray(MyArray&& other) noexcept
		: m_data(other.m_data)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	~MyArray() noexcept
	{
		delete[] m_data;
	}

	MyArray& operator=(const MyArray& other) noexcept
	{
		if (this != &other)
		{
			MyArray temp(other);
			Swap(temp);
		}

		return *this;
	}

	MyArray& operator=(MyArray&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_data;

			m_data = other.m_data;
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			other.m_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

		return *this;
	}

	template <typename U>
	MyArray& operator=(const MyArray<U>& other)
	{
		MyArray temp;

		temp.Resize(other.GetSize());

		for (size_t i = 0; i < other.GetSize(); ++i)
		{
			temp[i] = static_cast<T>(other[i]);
		}

		Swap(temp);

		return *this;
	}

	void PushBack(const T& value)
	{
		EnsureCapacity();

		m_data[m_size] = value;
		m_size++;
	}

	void PushBack(T&& value)
	{
		EnsureCapacity();

		m_data[m_size] = std::move(value);
		m_size++;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	size_t GetCapacity() const
	{
		return m_capacity;
	}

	void Resize(size_t newSize)
	{
		if (newSize <= m_capacity)
		{
			if (newSize > m_size)
			{
				for (size_t i = m_size; i < newSize; ++i)
				{
					m_data[i] = T();
				}
			}

			m_size = newSize;
			return;
		}

		size_t newCapacity = std::max(newSize, !m_capacity ? 1 : m_capacity * 2);

		T* newData = new T[newCapacity];

		try
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				newData[i] = m_data[i];
			}

			for (size_t i = m_size; i < newSize; ++i)
			{
				newData[i] = T();
			}
		}
		catch (...)
		{
			delete[] newData;
			throw;
		}

		delete[] m_data;

		m_data = newData;
		m_capacity = newCapacity;
		m_size = newSize;
	}

	void Clear() 
	{
        delete[] m_data;

		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	T& operator[](size_t index)
	{
		CheckIndex(index);
		return m_data[index];
	}

	const T& operator[](size_t index) const
	{
		CheckIndex(index);
		return m_data[index];
	}

	Iterator begin()
	{
		return Iterator(m_data);
	}

	Iterator end()
	{
		return Iterator(m_data + m_size);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_data);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_data + m_size);
	}

	ReverseIterator rbegin()
	{
		return ReverseIterator(end());
	}

	ReverseIterator rend()
	{
		return ReverseIterator(begin());
	}

	ConstIterator cend() const
	{
		return ConstIterator(end());
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(begin());
	}

	ConstReverseIterator crbegin() const
	{
		return ConstReverseIterator(cend());
	}

	ConstReverseIterator crend() const
	{
		return ConstReverseIterator(cbegin());
	}

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;

	void EnsureCapacity()
	{
		if (m_size < m_capacity)
		{
			return;
		}

		size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;

		T* newData = new T[newCapacity];

		try
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				newData[i] = std::move(m_data[i]);
			}
		}
		catch (...)
		{
			delete[] newData;
			throw;
		}

		delete[] m_data;

		m_data = newData;
		m_capacity = newCapacity;
	}

	void CopyFrom(const MyArray& other)
	{
		if (!other.m_size)
		{
			return;
		}
		T* newData = new T[other.m_capacity];

		try
		{
			for (size_t i = 0; i < other.m_size; ++i)
			{
				newData[i] = other.m_data[i];
			}
		}
		catch (...)
		{
			delete[] newData;
			throw;
		}

		m_data = newData;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
	}

	void Swap(MyArray& other) noexcept
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
	}

	void CheckIndex(size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("index out of range");
		}
	}

	void CreateObjects(size_t Length)
	{
	}
};