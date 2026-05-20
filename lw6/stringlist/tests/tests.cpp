#include "StringList.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

class ListFixture : public ::testing::Test
{
protected:
	StringList list;

	void SetUp() override
	{
		list.PushBack("1");
		list.PushBack("2");
		list.PushBack("3");
	}

	void TearDown() override
	{
		list.Clear();
	}
};

TEST(ListConstructorTest, DefaultConstructorValid)
{
	StringList list;
	ASSERT_EQ(list.IsEmpty(), true);
	ASSERT_EQ(list.Size(), 0);
}

TEST(ListConstructorTest, CopyConstructorValid)
{
	StringList list;
	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	StringList list1(list);

	auto iter = list.begin();
	auto iter1 = list1.begin();
	for (size_t i = 0; i < list.Size(); i++)
	{
		ASSERT_EQ(*iter, *iter1);
		iter++;
		iter1++;
	}
}

TEST(ListConstructorTest, CopyConstructorIndependent)
{
	StringList list;
	list.PushBack("1");

	StringList list1(list);
	list1.PushBack("2");

	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(list1.Size(), 2);
}

TEST(ListConstructorTest, MoveConstructorValid)
{
	StringList list;
	list.PushBack("1");
	list.PushBack("2");

	StringList list1(std::move(list));

	ASSERT_EQ(list1.Size(), 2);
	ASSERT_EQ(list.IsEmpty(), true);

	auto it = list1.begin();
	ASSERT_EQ(*it++, "1");
	ASSERT_EQ(*it, "2");
}

TEST(ListConstructorTest, CopyAssignValid)
{
	StringList list;
	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	StringList list1;
	list1 = list;

	auto iter = list.begin();
	auto iter1 = list1.begin();
	for (size_t i = 0; i < list.Size(); i++)
	{
		ASSERT_EQ(*iter, *iter1);
		iter++;
		iter1++;
	}
}

TEST(ListConstructorTest, CopyAssignIndependent)
{
	StringList list;
	list.PushBack("1");

	StringList list1;
	list1 = list;
	list1.PushBack("2");

	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(list1.Size(), 2);
}

TEST(ListConstructorTest, CopyAssignSelf)
{
	StringList list;
	list.PushBack("1");
	list = list;
	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(*list.begin(), "1");
}

TEST(ListConstructorTest, MoveAssignValid)
{
	StringList list;
	list.PushBack("1");
	list.PushBack("2");

	StringList list1;
	list1 = std::move(list);

	ASSERT_EQ(list1.Size(), 2);
	ASSERT_EQ(list.IsEmpty(), true);

	auto it = list1.begin();
	ASSERT_EQ(*it++, "1");
	ASSERT_EQ(*it, "2");
}

TEST_F(ListFixture, PushBackAddsToEnd)
{
	list.PushBack("4");
	ASSERT_EQ(list.Size(), 4);

	auto it = list.begin();
	std::advance(it, 3);
	ASSERT_EQ(*it, "4");
}

TEST_F(ListFixture, PushFrontAddsToFront)
{
	list.PushFront("0");
	ASSERT_EQ(list.Size(), 4);
	ASSERT_EQ(*list.begin(), "0");
}

TEST_F(ListFixture, InsertInMiddle)
{
	auto it = ++list.begin();
	list.Insert(it, "X");

	ASSERT_EQ(list.Size(), 4);

	it = list.begin();
	ASSERT_EQ(*it++, "1");
	ASSERT_EQ(*it++, "X");
	ASSERT_EQ(*it++, "2");
	ASSERT_EQ(*it, "3");
}

TEST_F(ListFixture, DeleteFirstElement)
{
	list.Delete(list.begin());
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*list.begin(), "2");
}

TEST_F(ListFixture, DeleteMiddleElement)
{
	list.Delete(++list.begin());
	ASSERT_EQ(list.Size(), 2);

	auto it = list.begin();
	ASSERT_EQ(*it++, "1");
	ASSERT_EQ(*it, "3");
}

TEST_F(ListFixture, DeleteEndThrows)
{
	ASSERT_THROW(list.Delete(list.end()), std::runtime_error);
}

TEST_F(ListFixture, DeleteReturnsNextIterator)
{
	auto it = list.Delete(list.begin());
	ASSERT_EQ(*it, "2");
}

TEST_F(ListFixture, SizeValid)
{
	ASSERT_EQ(list.Size(), 3);
}

TEST_F(ListFixture, IsEmptyFalse)
{
	ASSERT_FALSE(list.IsEmpty());
}

TEST_F(ListFixture, ClearMakesEmpty)
{
	list.Clear();
	ASSERT_TRUE(list.IsEmpty());
	ASSERT_EQ(list.Size(), 0);
}

TEST_F(ListFixture, ForwardIterationValid)
{
	std::vector<std::string> expected = { "1", "2", "3" };
	std::vector<std::string> actual;
	for (auto& s : list)
		actual.push_back(s);

	ASSERT_EQ(actual, expected);
}

TEST_F(ListFixture, aa)
{
	try
	{
		while (1)
		{
			list.PushBack("5");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		std::cout << list.Size() << "\n";
	}

	std::vector<std::string> expected = { "1", "2", "3" };
	std::vector<std::string> actual;
	for (auto it = list.begin(); it != list.end(); ++it)
		actual.push_back(*it);

	ASSERT_EQ(actual, expected);
}

TEST_F(ListFixture, IterationValid)
{
	std::vector<std::string> expected = { "1", "2", "3" };
	std::vector<std::string> actual;
	for (auto it = list.begin(); it != list.end(); ++it)
		actual.push_back(*it);

	ASSERT_EQ(actual, expected);
}

TEST_F(ListFixture, ConstIterationValid)
{
	std::vector<std::string> expected = { "1", "2", "3" };
	std::vector<std::string> actual;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
		actual.push_back(*it);

	ASSERT_EQ(actual, expected);
}

TEST_F(ListFixture, ReverseIterationValid)
{
	std::vector<std::string> expected = { "3", "2", "1" };
	std::vector<std::string> actual;
	for (auto it = list.rbegin(); it != list.rend(); ++it)
		actual.push_back(*it);

	ASSERT_EQ(actual, expected);
}

TEST_F(ListFixture, ConstReverseIterationValid)
{
	std::vector<std::string> expected = { "3", "2", "1" };
	std::vector<std::string> actual;
	for (auto it = list.crbegin(); it != list.crend(); ++it)
		actual.push_back(*it);

	ASSERT_EQ(actual, expected);
}
