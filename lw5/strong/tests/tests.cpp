#include "Strong.h"

#include <gtest/gtest.h>

#include <cstring>
#include <sstream>
#include <string>
#include <utility>

TEST(Strong, Default)
{
	Strong s;
	EXPECT_EQ(s.GetLength(), 0);
	EXPECT_EQ(s.GetStringData()[0], '\0');
}

TEST(Strong, FromCString)
{
	Strong s("hello");
	EXPECT_EQ(s.GetLength(), 5);
	EXPECT_STREQ(s.GetStringData(), "hello");
}

TEST(Strong, FromCStringLength)
{
	Strong s("abcdef", 3);
	EXPECT_EQ(s.GetLength(), 3);
	EXPECT_STREQ(s.GetStringData(), "abc");
}

TEST(Strong, FromString)
{
	Strong s(std::string("stl"));
	EXPECT_STREQ(s.GetStringData(), "stl");
}

TEST(Strong, CopyIndependent)
{
	Strong a("src");
	Strong b(a);
	EXPECT_STREQ(b.GetStringData(), "src");
	EXPECT_NE(a.GetStringData(), b.GetStringData());
}

TEST(Strong, MoveTransfersAndDonorValid)
{
	Strong a("moved");
	Strong b(std::move(a));
	EXPECT_STREQ(b.GetStringData(), "moved");
	EXPECT_EQ(a.GetLength(), 0);
	EXPECT_EQ(a.GetStringData()[0], '\0');
}

TEST(Strong, ClearMakesEmpty)
{
	Strong s("hello");
	s.Clear();
	EXPECT_EQ(s.GetLength(), 0);
	EXPECT_EQ(s.GetStringData()[0], '\0');
}

TEST(Strong, SubStringBasic)
{
	Strong s("abcdef");
	EXPECT_STREQ(s.SubString(1, 3).GetStringData(), "bcd");
	EXPECT_STREQ(s.SubString(3).GetStringData(), "def");
	EXPECT_STREQ(s.SubString(2, 100).GetStringData(), "cdef");
}

TEST(Strong, SubStringOutOfRangeThrows)
{
	Strong s("abc");
	EXPECT_THROW(s.SubString(4, 1), std::out_of_range);
}

TEST(Strong, CopyChain)
{
	Strong a("old"), b("new"), c;
	c = a = b;
	EXPECT_STREQ(a.GetStringData(), "new");
	EXPECT_STREQ(c.GetStringData(), "new");
}

TEST(Strong, SelfAssign)
{
	Strong s("self");
	s = s;
	EXPECT_STREQ(s.GetStringData(), "self");
}

TEST(Strong, MovementCheckDonor)
{
	Strong a("old"), b("new");
	a = std::move(b);
	EXPECT_STREQ(a.GetStringData(), "new");
	EXPECT_EQ(b.GetLength(), 0);
	EXPECT_EQ(b.GetStringData()[0], '\0');
}

TEST(Strong, PlusTest)
{
	Strong s("world");
	EXPECT_STREQ((Strong("hi ") + s).GetStringData(), "hi world");
	EXPECT_STREQ((std::string("hi ") + s).GetStringData(), "hi world");
	EXPECT_STREQ(("hi " + s).GetStringData(), "hi world");
}

TEST(Strong, PlusEquel)
{
	Strong a("ab");
	a += Strong("cd");
	EXPECT_STREQ(a.GetStringData(), "abcd");

	Strong b("xy");
	b += b;
	EXPECT_STREQ(b.GetStringData(), "xyxy");
}

TEST(Strong, CapacityX2)
{
	Strong s("0123456789");
	size_t capBefore = s.GetCapacity();
	s += Strong("X");
	EXPECT_GE(s.GetCapacity(), capBefore * 2);
	EXPECT_STREQ(s.GetStringData(), "0123456789X");
}

TEST(Strong, Comparisons)
{
	EXPECT_TRUE(Strong("abc") == Strong("abc"));
	EXPECT_TRUE(Strong("abc") != Strong("abd"));
	EXPECT_TRUE(Strong("abc") < Strong("abd"));
	EXPECT_TRUE(Strong("abd") > Strong("abc"));
	EXPECT_TRUE(Strong("abc") <= Strong("abc"));
	EXPECT_TRUE(Strong("abc") >= Strong("abc"));
	EXPECT_TRUE(Strong("abc") < Strong("abcd"));
}

TEST(Strong, OperatorIndex)
{
	Strong s("abc");
	EXPECT_EQ(s[0], 'a');
	s[0] = 'X';
	EXPECT_STREQ(s.GetStringData(), "Xbc");

	const Strong cs("xyz");
	EXPECT_EQ(cs[1], 'y');
}

TEST(Strong, StreamOutput)
{
	std::ostringstream oss;
	oss << Strong("hello");
	EXPECT_EQ(oss.str(), "hello");
}

TEST(Strong, StreamInput)
{
	std::istringstream iss("  hello world");
	Strong s;
	iss >> s;
	EXPECT_STREQ(s.GetStringData(), "hello");
}

TEST(IteratorTest, ForwardForOperator)
{
	Strong s("hello");

	std::string result;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		result += *it;
	}

	EXPECT_EQ(result, "hello");
}

TEST(IteratorTest, RangeBasedFor)
{
	Strong s("abc");

	std::string result;
	for (char c : s)
	{
		result += c;
	}

	EXPECT_EQ(result, "abc");
}

TEST(IteratorTest, ConstIter)
{
	const Strong s("world");

	std::string result;
	for (auto it = s.cbegin(); it != s.cend(); ++it)
	{
		result += *it;
	}

	EXPECT_EQ(result, "world");
}

TEST(IteratorTest, ReverseIteration)
{
	Strong s("abc");

	std::string result;
	for (auto it = s.rbegin(); it < s.rend(); ++it)
	{
		result += *it;
	}

	EXPECT_EQ(result, "cba");
}

TEST(IteratorTest, ConstReverseIteration)
{
	const Strong s("abc");

	std::string result;
	for (auto it = s.crbegin(); it < s.crend(); ++it)
	{
		result += *it;
	}

	EXPECT_EQ(result, "cba");
}

TEST(IteratorTest, IncrementAndDereference)
{
	Strong s("xyz");

	auto it = s.begin();

	EXPECT_EQ(*it, 'x');
	++it;
	EXPECT_EQ(*it, 'y');
	++it;
	EXPECT_EQ(*it, 'z');
}

TEST(IteratorTest, Decrement)
{
	Strong s("xyz");

	auto it = s.end();
	--it;
	EXPECT_EQ(*it, 'z');
	--it;
	EXPECT_EQ(*it, 'y');
}

TEST(IteratorTest, CopyIterator)
{
	Strong s("ab");
	auto it1 = s.begin();
	auto it2 = it1;

	++it1;

	EXPECT_EQ(*it1, 'b');
	EXPECT_EQ(*it2, 'a');
}

TEST(IteratorTest, ComparisonOperators)
{
	Strong s("ab");

	auto it1 = s.begin();
	auto it2 = s.begin();

	EXPECT_TRUE(it1 == it2);
	EXPECT_TRUE(it1 != ++it2);
	EXPECT_TRUE(it1 < it2);
	EXPECT_TRUE(it2 > it1);
	EXPECT_TRUE(it1 <= it2);
	EXPECT_TRUE(--it2 >= it1);
}

TEST(IteratorTest, EmptyContainer)
{
	Strong s("");

	EXPECT_TRUE(s.begin() == s.end());
}

TEST(IteratorTest, OutOfRangeAssert)
{
	Strong container("hello");
	auto it = container.end();

	EXPECT_DEATH(*it, "iter: out of range");
}

TEST(IteratorTest, ConstIteratorValueIsConst)
{
	Strong s("hello");
	
	using ItRef = decltype(*s.cbegin());
	static_assert(std::is_const_v<std::remove_reference_t<ItRef>>);

	using ItRef = decltype(*s.crbegin());
	static_assert(std::is_const_v<std::remove_reference_t<ItRef>>);

	using ItRef = decltype(*s.crend());
	static_assert(std::is_const_v<std::remove_reference_t<ItRef>>);

	using ItRef = decltype(*s.cend());
	static_assert(std::is_const_v<std::remove_reference_t<ItRef>>);
}
