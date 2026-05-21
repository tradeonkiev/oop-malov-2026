#include "MyArray.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

TEST(MyArray, IsEmptyAfterDefaultConstruction)
{
	MyArray<int> arr;

	EXPECT_EQ(arr.GetSize(), 0);
	EXPECT_EQ(arr.GetCapacity(), 0);
}

TEST(MyArray, PushBackAddsElementsToEnd)
{
	MyArray<int> arr;

	arr.PushBack(10);
	arr.PushBack(20);
	arr.PushBack(30);

	ASSERT_EQ(arr.GetSize(), 3);
	EXPECT_EQ(arr[0], 10);
	EXPECT_EQ(arr[1], 20);
	EXPECT_EQ(arr[2], 30);
}

TEST(MyArray, PushBackSupportsMoveOnlyRvalueLikeStrings)
{
	MyArray<std::string> arr;

	std::string value = "hello";
	arr.PushBack(std::move(value));
	arr.PushBack("world");

	ASSERT_EQ(arr.GetSize(), 2);
	EXPECT_EQ(arr[0], "hello");
	EXPECT_EQ(arr[1], "world");
}

TEST(MyArray, CapacityDoublesWhenPushingElements)
{
	MyArray<int> arr;

	EXPECT_EQ(arr.GetCapacity(), 0);

	arr.PushBack(1);
	EXPECT_EQ(arr.GetCapacity(), 1);

	arr.PushBack(2);
	EXPECT_EQ(arr.GetCapacity(), 2);

	arr.PushBack(3);
	EXPECT_EQ(arr.GetCapacity(), 4);

	arr.PushBack(4);
	EXPECT_EQ(arr.GetCapacity(), 4);

	arr.PushBack(5);
	EXPECT_EQ(arr.GetCapacity(), 8);
}

TEST(MyArray, OperatorSquareBracketsThrowsWhenIndexOutOfRange)
{
	MyArray<int> arr;

	arr.PushBack(42);

	EXPECT_NO_THROW(arr[0]);
	EXPECT_THROW(arr[1], std::out_of_range);
	EXPECT_THROW(arr[100], std::out_of_range);
}

TEST(MyArray, ConstOperatorSquareBracketsThrowsWhenIndexOutOfRange)
{
	MyArray<std::string> arr;
	arr.PushBack("one");

	const MyArray<std::string> constArr = arr;

	EXPECT_EQ(constArr[0], "one");
	EXPECT_THROW(constArr[1], std::out_of_range);
}

TEST(MyArray, OperatorSquareBracketsAllowsChangingElement)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr[0] = 99;

	EXPECT_EQ(arr[0], 99);
}

TEST(MyArray, ResizeCanIncreaseSizeAndDefaultInitializeNewElements)
{
	MyArray<int> arr;

	arr.PushBack(10);
	arr.PushBack(20);

	arr.Resize(5);

	ASSERT_EQ(arr.GetSize(), 5);
	EXPECT_EQ(arr[0], 10);
	EXPECT_EQ(arr[1], 20);
	EXPECT_EQ(arr[2], 0);
	EXPECT_EQ(arr[3], 0);
	EXPECT_EQ(arr[4], 0);
}

TEST(MyArray, ResizeCanIncreaseStringArrayAndDefaultInitializeNewElements)
{
	MyArray<std::string> arr;

	arr.PushBack("hello");

	arr.Resize(3);

	ASSERT_EQ(arr.GetSize(), 3);
	EXPECT_EQ(arr[0], "hello");
	EXPECT_EQ(arr[1], "");
	EXPECT_EQ(arr[2], "");
}

TEST(MyArray, ResizeCanDecreaseSize)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);
	arr.PushBack(3);
	arr.PushBack(4);

	arr.Resize(2);

	ASSERT_EQ(arr.GetSize(), 2);
	EXPECT_EQ(arr[0], 1);
	EXPECT_EQ(arr[1], 2);
	EXPECT_THROW(arr[2], std::out_of_range);
}

TEST(MyArray, ResizeToZeroMakesArrayEmptyButMayKeepCapacity)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);

	const size_t oldCapacity = arr.GetCapacity();

	arr.Resize(0);

	EXPECT_EQ(arr.GetSize(), 0);
	EXPECT_EQ(arr.GetCapacity(), oldCapacity);
	EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(MyArray, ClearRemovesAllElementsAndCapacity)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);
	arr.PushBack(3);

	arr.Clear();

	EXPECT_EQ(arr.GetSize(), 0);
	EXPECT_EQ(arr.GetCapacity(), 0);
	EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(MyArray, CopyConstructorCopiesElements)
{
	MyArray<std::string> source;

	source.PushBack("one");
	source.PushBack("two");

	MyArray<std::string> copy(source);

	ASSERT_EQ(copy.GetSize(), 2);
	EXPECT_EQ(copy[0], "one");
	EXPECT_EQ(copy[1], "two");

	copy[0] = "changed";

	EXPECT_EQ(source[0], "one");
	EXPECT_EQ(copy[0], "changed");
}

TEST(MyArray, CopyAssignmentCopiesElements)
{
	MyArray<int> source;

	source.PushBack(10);
	source.PushBack(20);

	MyArray<int> target;

	target.PushBack(1);
	target.PushBack(2);
	target.PushBack(3);

	target = source;

	ASSERT_EQ(target.GetSize(), 2);
	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 20);

	target[0] = 100;

	EXPECT_EQ(source[0], 10);
	EXPECT_EQ(target[0], 100);
}

TEST(MyArray, CopyAssignmentToSelfKeepsArrayValid)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);

	arr = arr;

	ASSERT_EQ(arr.GetSize(), 2);
	EXPECT_EQ(arr[0], 1);
	EXPECT_EQ(arr[1], 2);
}

TEST(MyArray, MoveConstructorMovesData)
{
	MyArray<std::string> source;

	source.PushBack("first");
	source.PushBack("second");

	MyArray<std::string> moved(std::move(source));

	ASSERT_EQ(moved.GetSize(), 2);
	EXPECT_EQ(moved[0], "first");
	EXPECT_EQ(moved[1], "second");

	EXPECT_EQ(source.GetSize(), 0);
	EXPECT_EQ(source.GetCapacity(), 0);
}

TEST(MyArray, MoveAssignmentMovesData)
{
	MyArray<std::string> source;

	source.PushBack("hello");
	source.PushBack("world");

	MyArray<std::string> target;

	target.PushBack("old");

	target = std::move(source);

	ASSERT_EQ(target.GetSize(), 2);
	EXPECT_EQ(target[0], "hello");
	EXPECT_EQ(target[1], "world");

	EXPECT_EQ(source.GetSize(), 0);
	EXPECT_EQ(source.GetCapacity(), 0);
}

TEST(MyArray, MoveAssignmentToSelfKeepsArrayValid)
{
	MyArray<int> arr;

	arr.PushBack(10);
	arr.PushBack(20);

	arr = std::move(arr);

	ASSERT_EQ(arr.GetSize(), 2);
	EXPECT_EQ(arr[0], 10);
	EXPECT_EQ(arr[1], 20);
}

TEST(MyArray, IteratorsAllowForwardTraversal)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);
	arr.PushBack(3);

	std::vector<int> values;

	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		values.push_back(*it);
	}

	EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(MyArray, IteratorsAllowRangeBasedFor)
{
	MyArray<std::string> arr;

	arr.PushBack("a");
	arr.PushBack("b");
	arr.PushBack("c");

	std::string result;

	for (const auto& item : arr)
	{
		result += item;
	}

	EXPECT_EQ(result, "abc");
}

TEST(MyArray, ReverseIteratorsAllowReverseTraversal)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);
	arr.PushBack(3);

	std::vector<int> values;

	for (auto it = arr.rbegin(); it != arr.rend(); ++it)
	{
		values.push_back(*it);
	}

	EXPECT_EQ(values, std::vector<int>({ 3, 2, 1 }));
}

TEST(MyArray, IteratorsAreRandomAccess)
{
	MyArray<int> arr;

	arr.PushBack(10);
	arr.PushBack(20);
	arr.PushBack(30);

	auto it = arr.begin();

	EXPECT_EQ(*it, 10);
	EXPECT_EQ(*(it + 1), 20);
	EXPECT_EQ(*(it + 2), 30);
	EXPECT_EQ(arr.end() - arr.begin(), 3);
	EXPECT_EQ(it[2], 30);
}

TEST(MyArray, IteratorCanBeUsedWithStandardAlgorithms)
{
	MyArray<int> arr;

	arr.PushBack(3);
	arr.PushBack(1);
	arr.PushBack(2);

	std::sort(arr.begin(), arr.end());

	ASSERT_EQ(arr.GetSize(), 3);
	EXPECT_EQ(arr[0], 1);
	EXPECT_EQ(arr[1], 2);
	EXPECT_EQ(arr[2], 3);
}

TEST(MyArray, ConstIteratorsAllowForwardTraversal)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);
	arr.PushBack(3);

	const MyArray<int>& constArr = arr;

	std::vector<int> values;

	for (auto it = constArr.cbegin(); it != constArr.cend(); ++it)
	{
		values.push_back(*it);
	}

	EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(MyArray, ConstReverseIteratorsAllowReverseTraversal)
{
	MyArray<int> arr;

	arr.PushBack(1);
	arr.PushBack(2);
	arr.PushBack(3);

	const MyArray<int>& constArr = arr;

	std::vector<int> values;

	for (auto it = constArr.crbegin(); it != constArr.crend(); ++it)
	{
		values.push_back(*it);
	}

	EXPECT_EQ(values, std::vector<int>({ 3, 2, 1 }));
}

TEST(MyArray, TemplateAssignmentConvertsElementsUsingStaticCast)
{
	MyArray<double> source;

	source.PushBack(1.2);
	source.PushBack(2.8);
	source.PushBack(3.9);

	MyArray<int> target;

	target.PushBack(100);

	target = source;

	ASSERT_EQ(target.GetSize(), 3);
	EXPECT_EQ(target[0], 1);
	EXPECT_EQ(target[1], 2);
	EXPECT_EQ(target[2], 3);
}

TEST(MyArray, TemplateAssignmentCanConvertIntToDouble)
{
	MyArray<int> source;

	source.PushBack(10);
	source.PushBack(20);

	MyArray<double> target;

	target = source;

	ASSERT_EQ(target.GetSize(), 2);
	EXPECT_DOUBLE_EQ(target[0], 10.0);
	EXPECT_DOUBLE_EQ(target[1], 20.0);
}

TEST(MyArray, WorksAsStringArray)
{
	MyArray<std::string> arr;

	arr.PushBack("ivan");
	arr.PushBack("petr");
	arr.PushBack("lesha");

	ASSERT_EQ(arr.GetSize(), 3);
	EXPECT_EQ(arr[0], "ivan");
	EXPECT_EQ(arr[1], "petr");
	EXPECT_EQ(arr[2], "lesha");
}

TEST(MyArray, WorksAsDoubleArray)
{
	MyArray<double> arr;

	arr.PushBack(1.5);
	arr.PushBack(2.25);
	arr.PushBack(3.75);

	ASSERT_EQ(arr.GetSize(), 3);
	EXPECT_DOUBLE_EQ(arr[0], 1.5);
	EXPECT_DOUBLE_EQ(arr[1], 2.25);
	EXPECT_DOUBLE_EQ(arr[2], 3.75);
}