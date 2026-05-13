#pragma once

#include "OwnIterator.h"
#include <compare>
#include <iterator>
#include <string>

class Strong
{
public:
	using Iterator = OwnIterator<char, Strong>;
	using ConstIterator = OwnIterator<const char, const Strong>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	// конструктор по умолчанию
	Strong();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	Strong(const char* pString);

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	Strong(const char* pString, size_t length);

	// конструктор копирования
	Strong(Strong const& other);

	// перемещающий конструктор
	//  реализуется совместно с перемещающим оператором присваивания
	Strong operator=(Strong&& other) noexcept;
	Strong(Strong&& other) noexcept;

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	Strong(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~Strong();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	Strong SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	// Возвращает вместимость строки
	size_t GetCapacity();
	Strong& operator=(const Strong& Other);

	std::strong_ordering operator<=>(const Strong& Other) const;
	bool operator==(const Strong& other) const;

	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	Strong& operator+=(const Strong& other);

	Iterator begin();
	Iterator end();

	ConstIterator begin() const;
	ConstIterator end() const;

	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();

	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

private:
	inline static char m_emptyString[1] = { '\0' };
	size_t m_size;
	size_t m_capacity;
	char* m_data;
};

Strong operator+(const Strong& left, const Strong& right);
Strong operator+(const std::string& left, const Strong& right);
Strong operator+(const char* left, const Strong& right);

std::ostream& operator<<(std::ostream& os, const Strong& string);
std::istream& operator>>(std::istream& is, Strong& string);