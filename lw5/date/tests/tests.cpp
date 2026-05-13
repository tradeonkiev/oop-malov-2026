#include "Date.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(DateTest, Def)
{
	Date d;
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970);
	EXPECT_TRUE(d.IsValid());
}

TEST(DateTest, DayMonthYear)
{
	Date d(15, Month::MARCH, 2023);
	EXPECT_EQ(d.GetDay(), 15);
	EXPECT_EQ(d.GetMonth(), Month::MARCH);
	EXPECT_EQ(d.GetYear(), 2023);
}

TEST(DateTest, ZeroInit)
{
	Date d(0);
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970);
}

TEST(DateTest, NextYearInit)
{
	Date d(365);
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1971);
}

TEST(DateTest, InvalidDay)
{
	Date d(0, Month::JANUARY, 2000);
	EXPECT_FALSE(d.IsValid());
}

TEST(DateTest, InvalidMonth)
{
	Date d(1, static_cast<Month>(13), 2000);
	EXPECT_FALSE(d.IsValid());
}

TEST(DateTest, InvalidYear1970)
{
	Date d(1, Month::JANUARY, 1969);
	EXPECT_FALSE(d.IsValid());
}

TEST(DateTest, InvalidFeb29)
{
	Date d(29, Month::FEBRUARY, 2001);
	EXPECT_FALSE(d.IsValid());
}

TEST(DateTest, ValidFeb29)
{
	Date d(29, Month::FEBRUARY, 2000);
	EXPECT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 29);
	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
}

TEST(DateTest, WeekDayThursday)
{
	Date d;
	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
}

TEST(DateTest, PrefixIncrement)
{
	Date d(31, Month::JANUARY, 2000);
	++d;
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
}

TEST(DateTest, PrefixDecrement)
{
	Date d(1, Month::MARCH, 2000);
	--d;
	EXPECT_EQ(d.GetDay(), 29);
	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
}

TEST(DateTest, DecrementEpoch)
{
	Date d(1, Month::JANUARY, 1970);
	--d;
	EXPECT_FALSE(d.IsValid());
}

TEST(DateTest, AddDays)
{
	Date d(28, Month::FEBRUARY, 2010);
	Date r = d + 3;
	EXPECT_EQ(r.GetDay(), 3);
	EXPECT_EQ(r.GetMonth(), Month::MARCH);
}

TEST(DateTest, SubtractDays)
{
	Date d(1, Month::JANUARY, 2010);
	Date r = d - 2;
	EXPECT_EQ(r.GetDay(), 30);
	EXPECT_EQ(r.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(r.GetYear(), 2009);
}

TEST(DateTest, DateDifference)
{
	Date d1(1, Month::JANUARY, 2010);
	Date d2(30, Month::DECEMBER, 2009);
	EXPECT_EQ(d1 - d2, 2);
	EXPECT_EQ(d2 - d1, -2);
}

TEST(DateTest, Comparison)
{
	Date d1(15, Month::MARCH, 2023);
	Date d2(15, Month::MARCH, 2023);
	Date d3(16, Month::MARCH, 2023);
	EXPECT_TRUE(d1 == d2);
	EXPECT_TRUE(d1 != d3);
	EXPECT_TRUE(d1 < d3);
	EXPECT_TRUE(d3 > d1);
}

TEST(DateTest, OutputFormat)
{
	Date d(5, Month::MARCH, 2023);
	std::ostringstream oss;
	oss << d;
	EXPECT_EQ(oss.str(), "5.3.2023");
}

TEST(DateTest, OutputInvalid)
{
	Date d(99, static_cast<Month>(99), 10983);
	std::ostringstream oss;
	oss << d;
	EXPECT_EQ(oss.str(), "INVALID");
}

TEST(DateTest, InputValid)
{
	Date d;
	std::istringstream iss("15.3.2023");
	iss >> d;
	EXPECT_EQ(d.GetDay(), 15);
	EXPECT_EQ(d.GetMonth(), Month::MARCH);
	EXPECT_EQ(d.GetYear(), 2023);
}

TEST(DateTest, OperatorInputOutput)
{
	std::ostringstream oss;
	std::istringstream iss("29.02.2004");

	Date date;
	iss >> date;

	EXPECT_EQ(date.GetDay(), 29);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2004);

	oss << ++date;
	EXPECT_EQ(oss.str(), "1.3.2004");
}

TEST(DateTest, LastDay)
{
	std::istringstream iss("31.12.9999");
	Date date;

	iss >> date;
	EXPECT_EQ(date.GetDay(), 31);
	EXPECT_EQ(date.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(date.GetYear(), 9999);
}
