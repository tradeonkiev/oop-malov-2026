#include "accumulate.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(ReadArray, ValidIntegers)
{
	std::istringstream input("1 2 3");
	auto result = ReadArray(input);
	ASSERT_EQ(result.size(), 3);
	EXPECT_DOUBLE_EQ(result[0], 1.0);
	EXPECT_DOUBLE_EQ(result[1], 2.0);
	EXPECT_DOUBLE_EQ(result[2], 3.0);
}

TEST(ReadArray, ValidDoubles)
{
	std::istringstream input("1.5 2.7 3.14");
	auto result = ReadArray(input);
	ASSERT_EQ(result.size(), 3);
	EXPECT_DOUBLE_EQ(result[0], 1.5);
	EXPECT_DOUBLE_EQ(result[1], 2.7);
	EXPECT_DOUBLE_EQ(result[2], 3.14);
}

TEST(ReadArray, NegativeNumbers)
{
	std::istringstream input("-1.0 -2.5 -3.0");
	auto result = ReadArray(input);
	ASSERT_EQ(result.size(), 3);
	EXPECT_DOUBLE_EQ(result[0], -1.0);
}

TEST(ReadArray, SingleNumber)
{
	std::istringstream input("42.0");
	auto result = ReadArray(input);
	ASSERT_EQ(result.size(), 1);
	EXPECT_DOUBLE_EQ(result[0], 42.0);
}

TEST(ReadArray, EmptyInput)
{
	std::istringstream input("");
	auto result = ReadArray(input);
	EXPECT_TRUE(result.empty());
}

TEST(ReadArray, ThrowsOnLetters)
{
	std::istringstream input("1.0 cok 3.0");
	EXPECT_THROW(ReadArray(input), std::invalid_argument);
}

TEST(CalcPositiveAverage, MixedNumbers)
{
	std::vector<double> arr = { -2.0, 3.0, -1.0, 5 };
	EXPECT_DOUBLE_EQ(CalcPositiveAverage(arr), 4.0);
}

TEST(CalcPositiveAverage, AllPositive)
{
	std::vector<double> arr = { 2.0, 4.0, 6.0 };
	EXPECT_DOUBLE_EQ(CalcPositiveAverage(arr), 4.0);
}

TEST(CalcPositiveAverage, AllNegative)
{
	std::vector<double> arr = { -1.0, -2.0, -3.0 };
	EXPECT_DOUBLE_EQ(CalcPositiveAverage(arr), 0.0);
}

TEST(CalcPositiveAverage, SinglePositive)
{
	std::vector<double> arr = { 7.5 };
	EXPECT_DOUBLE_EQ(CalcPositiveAverage(arr), 7.5);
}

TEST(CalcPositiveAverage, EmptyArray)
{
	std::vector<double> arr = {};
	EXPECT_DOUBLE_EQ(CalcPositiveAverage(arr), 0.0);
}

TEST(CalcPositiveAverage, ZerosIgnored)
{
	std::vector<double> arr = { 0.0, 0.0, 3.0 };
	EXPECT_DOUBLE_EQ(CalcPositiveAverage(arr), 3.0);
}

TEST(PrintArray, FormatsCorrectly)
{
	std::vector<double> arr = { 1.0, 2.5, 3.14 };
	std::ostringstream output;
	PrintArray(arr, output);
	EXPECT_EQ(output.str(), "1.000 2.500 3.140\n");
}

TEST(PrintArray, SingleElement)
{
	std::vector<double> arr = { 5.0 };
	std::ostringstream output;
	PrintArray(arr, output);
	EXPECT_EQ(output.str(), "5.000\n");
}

TEST(PrintArray, EmptyArray)
{
	std::vector<double> arr = {};
	std::ostringstream output;
	PrintArray(arr, output);
	EXPECT_EQ(output.str(), "");
}

TEST(PrintArray, NegativeNumbers)
{
	std::vector<double> arr = { -1.5, 2.0 };
	std::ostringstream output;
	PrintArray(arr, output);
	EXPECT_EQ(output.str(), "-1.500 2.000\n");
}