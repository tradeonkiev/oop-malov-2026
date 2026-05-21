#include <iterator>

template <typename T>
class MyIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	MyIterator(pointer ptr = nullptr)
		: m_ptr(ptr)
	{
	}

	reference operator*() const
	{
		return *m_ptr;
	}

	MyIterator& operator++()
	{
		++m_ptr;
		return *this;
	}

	MyIterator operator++(int)
	{
		MyIterator temp(*this);
		++(*this);
		return temp;
	}

	MyIterator& operator--()
	{
		--m_ptr;
		return *this;
	}

	MyIterator operator--(int)
	{
		MyIterator temp(*this);
		--(*this);
		return temp;
	}

	MyIterator operator+(difference_type n) const
	{
		return MyIterator(m_ptr + n);
	}

	MyIterator operator-(difference_type n) const
	{
		return MyIterator(m_ptr - n);
	}

	difference_type operator-(const MyIterator& other) const
	{
		return m_ptr - other.m_ptr;
	}

	MyIterator& operator+=(difference_type n)
	{
		m_ptr += n;
		return *this;
	}

	MyIterator& operator-=(difference_type n)
	{
		m_ptr -= n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return m_ptr[n];
	}

	bool operator==(const MyIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const MyIterator& other) const
	{
		return m_ptr != other.m_ptr;
	}

	bool operator<(const MyIterator& other) const
	{
		return m_ptr < other.m_ptr;
	}

	bool operator>(const MyIterator& other) const
	{
		return m_ptr > other.m_ptr;
	}

	bool operator<=(const MyIterator& other) const
	{
		return m_ptr <= other.m_ptr;
	}

	bool operator>=(const MyIterator& other) const
	{
		return m_ptr >= other.m_ptr;
	}

private:
	pointer m_ptr;
};
