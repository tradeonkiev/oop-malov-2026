#include "FindMaxEx.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

struct Person
{
	std::string fullName;
	double height;
	double weight;

	bool operator==(Person const& o) const
	{
		return fullName == o.fullName
			&& height == o.height
			&& weight == o.weight;
	}
};

struct LessByHeight
{
	bool operator()(Person const& a, Person const& b) const
	{
		return a.height < b.height;
	}
};

struct LessByWeight
{
	bool operator()(Person const& a, Person const& b) const
	{
		return a.weight < b.weight;
	}
};

class FindMaxExFixture : public ::testing::Test
{
protected:
	std::vector<Person> athletes;

	void SetUp() override
	{
		athletes = {
			{ "ivanov sergey", 185.0, 82.5 },
			{ "smirnov sergeu", 178.0, 95.0 },
			{ "kozlov sergey", 192.0, 88.0 },
			{ "novikov sergey", 175.0, 74.0 },
			{ "dkflbvbhjdf sergey", 189.0, 91.5 },
		};
	}
};

TEST(FindMaxExEmptyTest, ReturnsFalseForEmptyVector)
{
	std::vector<int> empty;
	int result = 0;
	ASSERT_FALSE(FindMaxEx(empty, result, [](int a, int b) { return a < b; }));
}

TEST(FindMaxExEmptyTest, DoesNotModifyOutParamOnEmpty)
{
	std::vector<int> empty;
	int result = 42;
	FindMaxEx(empty, result, [](int a, int b) { return a < b; });
	ASSERT_EQ(result, 42);
}

TEST(FindMaxExIntTest, ReturnsTrueForNonEmpty)
{
	std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2 };
	int result = 0;
	ASSERT_TRUE(FindMaxEx(v, result, [](int a, int b) { return a < b; }));
}

TEST(FindMaxExIntTest, FindsMaxInt)
{
	std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2 };
	int result = 0;
	FindMaxEx(v, result, [](int a, int b) { return a < b; });
	ASSERT_EQ(result, 9);
}

TEST(FindMaxExIntTest, FindsMinUsingReversedPredicate)
{
	std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2 };
	int result = 0;
	FindMaxEx(v, result, [](int a, int b) { return a > b; });
	ASSERT_EQ(result, 1);
}

TEST(FindMaxExIntTest, SingleElementReturnsItself)
{
	std::vector<int> v = { 7 };
	int result = 0;
	FindMaxEx(v, result, [](int a, int b) { return a < b; });
	ASSERT_EQ(result, 7);
}

TEST(FindMaxExIntTest, AllEqualElementsReturnsFirst)
{
	std::vector<int> v = { 5, 5, 5, 5 };
	int result = 0;
	FindMaxEx(v, result, [](int a, int b) { return a < b; });
	ASSERT_EQ(result, 5);
}

TEST(FindMaxExIntTest, NegativeNumbers)
{
	std::vector<int> v = { -10, -3, -7, -1, -5 };
	int result = 0;
	FindMaxEx(v, result, [](int a, int b) { return a < b; });
	ASSERT_EQ(result, -1);
}

TEST(FindMaxExStringTest, FindsLexicographicMax)
{
	std::vector<std::string> v = {
		"banana",
		"apple",
		"banana1",
		"strawberry"
	};
	std::string result;
	FindMaxEx(v, result, [](std::string const& a, std::string const& b) {
		return a < b;
	});
	ASSERT_EQ(result, "strawberry");
}

TEST(FindMaxExStringTest, FindsLongestString)
{
	std::vector<std::string> v = {
		"hi",
		"hello",
		"hey",
	};
	std::string result;
	FindMaxEx(v, result, [](std::string const& a, std::string const& b) {
		return a.size() < b.size();
	});
	ASSERT_EQ(result, "hello");
}

TEST(FindMaxExStringTest, FindsShortestStringViaReversedPredicate)
{
	std::vector<std::string> v = { "hi", "hello", "hey" };

	std::string result;
	FindMaxEx(v, result, [](std::string const& a, std::string const& b) {
		return a.size() > b.size();
	});
	ASSERT_EQ(result, "hi");
}

TEST_F(FindMaxExFixture, FindsTallestAthlete)
{
	Person result{};
	ASSERT_TRUE(FindMaxEx(athletes, result, LessByHeight{}));
	ASSERT_EQ(result.fullName, "kozlov sergey");
	ASSERT_DOUBLE_EQ(result.height, 192.0);
}

TEST_F(FindMaxExFixture, FindsHeaviestAthlete)
{
	Person result{};
	ASSERT_TRUE(FindMaxEx(athletes, result, LessByWeight{}));
	ASSERT_EQ(result.fullName, "smirnov sergeu");
	ASSERT_DOUBLE_EQ(result.weight, 95.0);
}

TEST_F(FindMaxExFixture, FindsShortestAthleteViaReversedPredicate)
{
	Person result{};
	FindMaxEx(athletes, result,
		[](Person const& a, Person const& b) { return a.height > b.height; });
	ASSERT_EQ(result.fullName, "novikov sergey");
	ASSERT_DOUBLE_EQ(result.height, 175.0);
}

TEST_F(FindMaxExFixture, FindsLightestAthleteViaReversedPredicate)
{
	Person result{};
	FindMaxEx(athletes, result,
		[](Person const& a, Person const& b) { return a.weight > b.weight; });
	ASSERT_EQ(result.fullName, "novikov sergey");
	ASSERT_DOUBLE_EQ(result.weight, 74.0);
}

TEST_F(FindMaxExFixture, ReturnsTrueForNonEmptyAthletes)
{
	Person result{};
	ASSERT_TRUE(FindMaxEx(athletes, result, LessByHeight{}));
}

TEST_F(FindMaxExFixture, ReturnsFalseForEmptyAthletes)
{
	std::vector<Person> empty;
	Person result{};
	ASSERT_FALSE(FindMaxEx(empty, result, LessByHeight{}));
}

TEST_F(FindMaxExFixture, SingleAthleteIsMax)
{
	std::vector<Person> single = { { "1", 170.0, 70.0 } };
	Person result{};
	FindMaxEx(single, result, LessByHeight{});
	ASSERT_EQ(result, single[0]);
}

TEST_F(FindMaxExFixture, FunctorAndLambdaGiveSameResult)
{
	Person byFunctor{}, byLambda{};
	FindMaxEx(athletes, byFunctor, LessByHeight{});
	FindMaxEx(athletes, byLambda,
		[](Person const& a, Person const& b) { return a.height < b.height; });
	ASSERT_EQ(byFunctor, byLambda);
}