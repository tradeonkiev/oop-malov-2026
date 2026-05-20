#pragma once
#include <cassert>
#include <compare>
#include <iterator>

template <typename node_t, typename value_t>
class OwnIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = value_t;
	using difference_type = std::ptrdiff_t;
	using pointer = value_t*;
	using reference = value_t&;

	OwnIterator()
		: m_ptr(nullptr)
	{
	}

	OwnIterator(node_t* ptr)
		: m_ptr(ptr)
	{
	}

	reference operator*() const
	{
		return m_ptr->data;
	}

	node_t* GetNode()
	{
		return m_ptr;
	}

	OwnIterator& operator++()
	{
		m_ptr = m_ptr->next;
		return *this;
	}

	OwnIterator operator++(int) &
	{
		OwnIterator temp = *this;
		m_ptr = m_ptr->next;

		return temp;
	}

	OwnIterator& operator--()
	{
		m_ptr = m_ptr->prev;

		return *this;
	}
	OwnIterator operator--(int) &
	{
		OwnIterator temp = *this;
		m_ptr = m_ptr->prev;

		return temp;
	}

	bool operator==(const OwnIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

private:
	node_t* m_ptr;
};
