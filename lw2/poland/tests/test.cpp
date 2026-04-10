#include "poland.h"
#include <gtest/gtest.h>

TEST(Evaluate, SingleArgs)
{
	EXPECT_EQ(EvaluateFromString("(+ 7)"), 7);
	EXPECT_EQ(EvaluateFromString("(* 8)"), 8);
	EXPECT_EQ(EvaluateFromString("(+ 2 3)"), 5);
	EXPECT_EQ(EvaluateFromString("(* 2 4)"), 8);
}

TEST(Evaluate, ThreeArgsPlus)
{
	EXPECT_EQ(EvaluateFromString("(+ 2 3 4)"), 9);
}

TEST(Evaluate, ThreeArgsMul)
{
	EXPECT_EQ(EvaluateFromString("(* 2 3 4)"), 24);
}

TEST(Evaluate, NestedMulInPlus)
{
	EXPECT_EQ(EvaluateFromString("(+ (* 2 3) (* 3 4))"), 18);
}

TEST(Evaluate, NestedPlusInMul)
{
	EXPECT_EQ(EvaluateFromString("(* (+ 1 2) (+ 3 1))"), 12);
}

TEST(Evaluate, DeepNesting)
{
	EXPECT_EQ(EvaluateFromString("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))"), 33);
}

TEST(Evaluate, NegativeNumber)
{
	EXPECT_EQ(EvaluateFromString("(+ -2 3)"), 1);
}

TEST(Evaluate, AllNegative)
{
	EXPECT_EQ(EvaluateFromString("(+ -1 -2 -3)"), -6);
}

TEST(Evaluate, NegativeMul)
{
	EXPECT_EQ(EvaluateFromString("(* -2 3)"), -6);
}

TEST(Evaluate, Zero)
{
	EXPECT_EQ(EvaluateFromString("(+ 0 0)"), 0);
}

TEST(Evaluate, MulByZero)
{
	EXPECT_EQ(EvaluateFromString("(* 5 0)"), 0);
}

TEST(Evaluate, MulByOne)
{
	EXPECT_EQ(EvaluateFromString("(* 1 1 1)"), 1);
}

// TODO: сделать с максинт мининт
TEST(Evaluate, LargeNumbers)
{
	EXPECT_EQ(EvaluateFromString("(+ 1000000 2000000)"), 3000000);
}

TEST(Evaluate, EmptyStringThrows)
{
	EXPECT_THROW(EvaluateFromString(""), std::invalid_argument);
}

TEST(Evaluate, NoParensThrows)
{
	EXPECT_THROW(EvaluateFromString("42"), std::invalid_argument);
}

TEST(Evaluate, UnknownOperationThrows)
{
	EXPECT_THROW(EvaluateFromString("(- 2 3)"), std::invalid_argument);
}

TEST(Evaluate, NoArgsThrows)
{
	EXPECT_THROW(EvaluateFromString("(+)"), std::invalid_argument);
}

TEST(Evaluate, UnmatchedOpenThrows)
{
	EXPECT_THROW(EvaluateFromString("(+ 2 3"), std::invalid_argument);
}

TEST(Evaluate, UnmatchedCloseThrows)
{
	EXPECT_THROW(EvaluateFromString("(+ 2 3))"), std::invalid_argument);
}

TEST(Evaluate, TrailingGarbageThrows)
{
	EXPECT_THROW(EvaluateFromString("(+ 2 3) abc"), std::invalid_argument);
}

TEST(Evaluate, EmptyParensThrows)
{
	EXPECT_THROW(EvaluateFromString("()"), std::invalid_argument);
}