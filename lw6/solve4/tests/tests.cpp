#include "Solve4.h"
#include <gtest/gtest.h>

TEST(InvalidArguments, LeadingCoefficientIsZero)
{
	ASSERT_THROW(Solve4(0, 1, 1, 1, 1), std::invalid_argument);
}

TEST(ValidEquations, EquationHasNoRealRoots)
{
	ASSERT_THROW(Solve4(2, 5, 56, 40, 48), std::domain_error);
}

TEST(ValidEquations, LeadingMember)
{
	auto solution = Solve4(1, 0, 0, 0, 0);

	ASSERT_EQ(solution.numRoots, 4);
	ASSERT_EQ(solution.roots[0], 0);
	ASSERT_EQ(solution.roots[1], 0);
	ASSERT_EQ(solution.roots[2], 0);
	ASSERT_EQ(solution.roots[3], 0);
}

TEST(ValidEquations, LeadedTwoDifferentRealRoots)
{
	auto solution = Solve4(1, 0, 3, 0, -4);

	ASSERT_EQ(solution.numRoots, 2);
	ASSERT_NEAR(solution.roots[0], -1, 1e-5);
	ASSERT_NEAR(solution.roots[1], 1, 1e-5);
}

TEST(ValidEquations, UnLeadedTwoDifferentRealRoots)
{
	auto solution = Solve4(-0.1, 23, 5, 1, 3);

	ASSERT_EQ(solution.numRoots, 2);
	ASSERT_NEAR(solution.roots[0], -0.557592, 1e-5);
	ASSERT_NEAR(solution.roots[1], 230.217, 1e-3);
}

TEST(ValidEquations, FourEqualRealRoots)
{
	auto solution = Solve4(1, -8, 24, -32, 16);

	ASSERT_EQ(solution.numRoots, 4);
	ASSERT_NEAR(solution.roots[0], 2, 1e-5);
	ASSERT_NEAR(solution.roots[1], 2, 1e-5);
	ASSERT_NEAR(solution.roots[2], 2, 1e-5);
	ASSERT_NEAR(solution.roots[3], 2, 1e-5);
}

TEST(ValidEquations, TwoDifferentAndTwoEqualRealRoots)
{
	auto solution = Solve4(1, -107, 3018, -8320, 5408);

	ASSERT_EQ(solution.numRoots, 4);
	ASSERT_NEAR(solution.roots[0], 1, 1e-5);
	ASSERT_NEAR(solution.roots[1], 2, 1e-5);
	ASSERT_NEAR(solution.roots[2], 52, 1e-5);
	ASSERT_NEAR(solution.roots[3], 52, 1e-5);
}

TEST(ValidEquations, FourDifferentRealRoots)
{
	auto solution = Solve4(1, 0, -5, 0, 4);

	ASSERT_EQ(solution.numRoots, 4);
	ASSERT_NEAR(solution.roots[0], -2, 1e-5);
	ASSERT_NEAR(solution.roots[1], -1, 1e-5);
	ASSERT_NEAR(solution.roots[2], 1, 1e-5);
	ASSERT_NEAR(solution.roots[3], 2, 1e-5);
}
