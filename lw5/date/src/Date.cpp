#include "Date.h"
#include <compare>
#include <iostream>

const int INVALID_TIMESTAMP = -1;
const int MAX_TIMESTAMP = 2932896;
const int DAYS_PER_400Y = 146097;
const int DAYS_PER_100Y = 36524;
const int DAYS_PER_4Y = 1461;
const int DAYS_IN_SHIFTED_MONTH[] = {
	31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29
};
const int DAYS_IN_MONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int DAYS_PER_370Y = 135080;

Date::Date()
	: m_days(0)
{
}

Date::Date(unsigned day, Month month, unsigned year)
	: m_days(DateToTimestamp(day, month, year)) {
	};

Date::Date(unsigned timestamp)
	: m_days(static_cast<int>(timestamp))
{
	if (m_days > MAX_TIMESTAMP)
	{
		m_days = INVALID_TIMESTAMP;
	}
}

DateData Date::TimestampToDate(int timestamp)
{
	int shiftedTimestamp = DAYS_PER_370Y + timestamp;
	int cicles400Y = shiftedTimestamp / DAYS_PER_400Y;
	int remDays = shiftedTimestamp % DAYS_PER_400Y;

	int cicles100Y = remDays / DAYS_PER_100Y;
	if (cicles100Y == 4)
	{
		cicles100Y--;
	}
	remDays -= cicles100Y * DAYS_PER_100Y;

	int cicles4Y = remDays / DAYS_PER_4Y;
	remDays -= cicles4Y * DAYS_PER_4Y;

	auto remYears = remDays / 365;
	if (remYears == 4)
	{
		remYears--;
	}
	remDays -= remYears * 365;

	int years = 1600 + remYears + 400 * cicles400Y + 100 * cicles100Y + 4 * cicles4Y;
	int months;
	for (months = 0; DAYS_IN_SHIFTED_MONTH[months] <= remDays; months++)
	{
		remDays -= DAYS_IN_SHIFTED_MONTH[months];
	}

	if (months >= 10)
	{
		months -= 12;
		years++;
	}

	DateData result;
	result.day = remDays + 1;
	result.month = static_cast<Month>(months + 3);
	result.year = years;
	return result;
}

int Date::DateToTimestamp(unsigned day, Month month, unsigned year)
{
	if (year < 1970 || year > 9999)
		return INVALID_TIMESTAMP;
	if (month < Month::JANUARY || month > Month::DECEMBER)
		return INVALID_TIMESTAMP;
	if (day < 1 || day > DaysInMonth(month, year))
		return INVALID_TIMESTAMP;

	int mon = static_cast<int>(month);
	if (mon <= 2)
	{
		year--;
	}

	year -= 1600;
	int totalDays = year / 400 * DAYS_PER_400Y;
	year %= 400;
	totalDays += year / 100 * DAYS_PER_100Y;
	year %= 100;
	totalDays += year / 4 * DAYS_PER_4Y;
	year %= 4;
	totalDays += year * 365;

	int shiftedMonth = (mon + 9) % 12;
	for (int i = 0; i < shiftedMonth; i++)
	{
		totalDays += DAYS_IN_SHIFTED_MONTH[i];
	}

	totalDays += (day - 1);
	// std::cout << "COUT: " << totalDays - DAYS_PER_370Y << std::endl;
	return totalDays - DAYS_PER_370Y;
}

int Date::DaysInMonth(Month month, int year)
{
	if (month == Month::FEBRUARY && IsLeapYear(year))
	{
		return 29;
	}
	return DAYS_IN_MONTH[static_cast<int>(month) - 1];
}

bool Date::IsLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::IsValid() const
{
	return m_days <= MAX_TIMESTAMP && m_days >= 0;
}

unsigned Date::GetDay() const
{
	if (!IsValid())
		return 0;
	return TimestampToDate(m_days).day;
}

Month Date::GetMonth() const
{
	if (!IsValid())
		return static_cast<Month>(0);
	return TimestampToDate(m_days).month;
}

unsigned Date::GetYear() const
{
	if (!IsValid())
		return 0;
	return TimestampToDate(m_days).year;
}

WeekDay Date::GetWeekDay() const
{
	if (!IsValid())
		return static_cast<WeekDay>(0);
	return static_cast<WeekDay>((m_days + 4) % 7);
}

Date& Date::operator++()
{
	if (IsValid())
	{
		m_days++;
		if (m_days > MAX_TIMESTAMP)
			m_days = INVALID_TIMESTAMP;
	}
	return *this;
}

Date Date::operator++(int)
{
	Date temp = *this;
	(*this) += 1;
	return temp;
}

Date& Date::operator--()
{
	if (IsValid())
	{
		m_days--;
		if (m_days < 0)
			m_days = INVALID_TIMESTAMP;
	}
	return *this;
}

Date Date::operator--(int)
{
	Date temp = *this;
	(*this) -= 1;
	return temp;
}

Date Date::operator+(int days) const
{
	if (!IsValid())
		return *this;
	int result = m_days + days;
	Date d;
	if (result < 0 || result > MAX_TIMESTAMP)
		d.m_days = INVALID_TIMESTAMP;
	else
		d.m_days = result;
	return d;
}

int Date::operator+(const Date& other) const
{
	return static_cast<int>(m_days + other.m_days);
}

Date Date::operator-(int days) const
{
	return *this + (-days);
}

int Date::operator-(const Date& other) const
{
	return static_cast<int>(m_days - other.m_days);
}

Date& Date::operator+=(int days)
{
	if (IsValid())
	{
		m_days += days;
		if (m_days < 0 || m_days > MAX_TIMESTAMP)
			m_days = INVALID_TIMESTAMP;
	}
	return *this;
}

Date& Date::operator-=(int days)
{
	*this += (-days);
	return *this;
}

// std::strong_ordering Date::operator<=>(const Date& other) const
// {
// 	return m_days <=> other.m_days;
// }

// bool Date::operator==(const Date& other) const
// {
// 	return m_days == other.m_days;
// }

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	if (!date.IsValid())
	{
		os << "INVALID";
	}
	else
	{
		auto comp = Date::TimestampToDate(date.m_days);
		os << comp.day << "." << static_cast<int>(comp.month) << "." << comp.year;
	}
	return os;
}

std::istream& operator>>(std::istream& input, Date& date)
{
	unsigned day, month, year;
	char dot1, dot2;

	if (input >> day >> dot1 >> month >> dot2 >> year)
	{
		if (dot1 == '.' && dot2 == '.')
		{
			Date temp(day, static_cast<Month>(month), year);
			date = temp;
		}
		else
		{
			date.m_days = INVALID_TIMESTAMP;
		}
	}
	else
	{
		date.m_days = INVALID_TIMESTAMP;
	}
	return input;
}