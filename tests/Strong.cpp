#include "Strong.h"
#include <cstring>

Strong::Strong()
	: m_capacity(0)
	, m_size(0)
	, m_data(m_emptyString) {};

Strong::Strong(const char* pString)
	: Strong(pString, std::strlen(pString))
{
}

Strong::Strong(const char* pString, size_t length)
{

	m_size = length;
	m_data = new char[length + 1];
	m_capacity = length + 1;
	std::memcpy(m_data, pString, length);
	m_data[length] = '\0';
}

Strong::Strong(const Strong& other)
	: Strong::Strong(other.m_data, other.m_size)
{
}

Strong& Strong::operator=(const Strong& other)
{

	if (m_data == other.m_data)
	{
		return *this;
	}

	delete[] m_data;
	m_data = new char[other.m_size + 1];
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	strcpy(m_data, other.m_data);

	return *this;
}

Strong Strong::operator=(Strong&& other) noexcept
{
	return Strong(std::move(other));
}

Strong::Strong(Strong&& other) noexcept
	: m_size(other.m_size)
	, m_capacity(other.m_capacity)
	, m_data(other.m_data)
{
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_data = m_emptyString;
}

Strong::Strong(const std::string& stlString)
	: Strong(stlString.data(), stlString.size())
{
}

Strong::~Strong()
{
	delete[] m_data;
}

size_t Strong::GetLength() const
{
	return m_size;
}

const char* Strong::GetStringData() const
{
	return m_data;
}

size_t Strong::GetCapacity()
{
	return m_capacity;
}

void Strong::Clear()
{
	*m_data = '\0';
	m_size = 0;
}

std::strong_ordering Strong::operator<=>(const Strong& other) const
{
	int cmp = std::strcmp(m_data, other.m_data);
	if (cmp < 0)
	{
		return std::strong_ordering::less;
	}

	if (cmp > 0)
	{
		return std::strong_ordering::greater;
	}

	return m_size <=> other.m_size;
}

bool Strong::operator==(const Strong& other) const
{
	return m_size == other.m_size && !std::strcmp(m_data, other.m_data);
}

char& Strong::operator[](size_t index)
{
	return m_data[index];
}

const char& Strong::operator[](size_t index) const
{
	return m_data[index];
}

Strong& Strong::operator+=(const Strong& other)
{
	if (m_size + other.m_size > m_capacity)
	{
		m_capacity = 2 * (m_size + other.m_size);
		char* newChars = new char[m_capacity + 1];
		std::memcpy(newChars, m_data, m_size);
		if (m_data != m_emptyString)
		{
			delete[] m_data;
		}
		m_data = newChars;
	}
	std::memcpy(m_data + m_size, other.m_data, other.m_size);
	m_size = m_size + other.m_size;
	m_data[m_size] = '\0';

	return *this;
}

Strong operator+(const Strong& left, const Strong& right)
{
	Strong result(left);
	result += right;
	return result;
}

Strong operator+(const std::string& left, const Strong& right)
{
	return Strong(left) + right;
}

Strong operator+(const char* left, const Strong& right)
{
	return Strong(left) + right;
}

std::ostream& operator<<(std::ostream& os, const Strong& string)
{
	return os << string.GetStringData();
}
