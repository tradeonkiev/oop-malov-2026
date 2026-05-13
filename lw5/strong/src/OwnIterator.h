#pragma once
#include <cassert>
#include <compare>
#include <iterator>

template <typename Type, typename ContainerType>
class OwnIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = Type;
	using difference_type = std::ptrdiff_t;
	using pointer = Type*;
	using reference = Type&;
	using container = ContainerType*;

	OwnIterator(pointer ptr, container cont)
		: m_ptr(ptr)
		, m_container(cont) {
		};

	reference operator*() const
	{
		assert(m_ptr && m_ptr >= m_container->GetStringData() && m_ptr < (m_container->GetStringData() + m_container->GetLength()) && "iter: out of range");
		return *m_ptr;
	}

	OwnIterator& operator+=(difference_type value)
	{
		assert(m_ptr + value >= m_container->GetStringData() && m_ptr + value <= (m_container->GetStringData() + m_container->GetLength()) && "iter: out of range");
		m_ptr += value;
		return *this;
	}

	OwnIterator& operator++()
	{
		return *this += 1;
	}

	OwnIterator operator++(int) &
	{
		OwnIterator tmp = *this;
		++*this;
		return tmp;
	}

	OwnIterator& operator--()
	{
		return *this += -1;
	}

	OwnIterator operator--(int) &
	{
		OwnIterator tmp = *this;
		--*this;
		return tmp;
	}

	OwnIterator operator+(difference_type value) const
	{
		OwnIterator tmp(m_ptr, m_container);
		tmp += value;
		return tmp;
	}

	difference_type operator-(const OwnIterator& rIter) const
	{
		return m_ptr - rIter.m_ptr;
	}

	OwnIterator& operator-=(difference_type value)
	{
		return *this += -value;
	}

	OwnIterator operator-(difference_type value)
	{
		OwnIterator tmp(m_ptr, m_container);
		tmp += -value;
		return tmp;
	}

	reference operator[](difference_type value) const
	{
		return *(*this + value);
	}

	std::strong_ordering operator<=>(const OwnIterator& other) const = default;

	bool operator==(const OwnIterator& rIter) const
	{
		return m_ptr == rIter.m_ptr;
	}

private:
	pointer m_ptr;
	container m_container;
};
