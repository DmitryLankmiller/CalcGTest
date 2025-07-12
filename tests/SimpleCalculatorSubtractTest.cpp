#include "CalculatorAndRandomFixture.h"
#include "CalculatorFixture.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>
#include <random>

TEST_F(CalculatorFixture, Subtract2And3IsEqualToMinus1) {
  auto result = calculator.Subtract(2, 3);

  ASSERT_EQ(result, -1);
}

TEST_F(CalculatorAndRandomFixture, SubtractZero) {
  std::uniform_int_distribution<int> dist(-std::numeric_limits<int>::max(),
                                          std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    EXPECT_EQ(calculator.Subtract(0, a), -a);
    EXPECT_EQ(calculator.Subtract(a, 0), a);
  }
}

TEST_F(CalculatorAndRandomFixture, SubtractRandoms) {
  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min() / 2,
                                          std::numeric_limits<int>::max() / 2);

  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    int b = dist(gen);
    auto result = a - b;
    EXPECT_EQ(calculator.Subtract(a, b), result);
  }
}

struct SubtractLimitsParams {
  int a;
  int b;
  int expected;
};

class NumericLimitsSubtractTest
    : public CalculatorFixture,
      public ::testing::WithParamInterface<SubtractLimitsParams> {};

INSTANTIATE_TEST_SUITE_P(
    Calc, NumericLimitsSubtractTest,
    ::testing::Values(SubtractLimitsParams{std::numeric_limits<int>::max(), 1,
                                           std::numeric_limits<int>::max() - 1},
                      SubtractLimitsParams{std::numeric_limits<int>::max(), 0,
                                           std::numeric_limits<int>::max()},
                      SubtractLimitsParams{std::numeric_limits<int>::max() - 1,
                                           -1, std::numeric_limits<int>::max()},
                      SubtractLimitsParams{std::numeric_limits<int>::max(),
                                           std::numeric_limits<int>::max(), 0},
                      SubtractLimitsParams{std::numeric_limits<int>::min(), -1,
                                           std::numeric_limits<int>::min() + 1},
                      SubtractLimitsParams{std::numeric_limits<int>::min(), 0,
                                           std::numeric_limits<int>::min()},
                      SubtractLimitsParams{std::numeric_limits<int>::min() + 1,
                                           1, std::numeric_limits<int>::min()},
                      SubtractLimitsParams{std::numeric_limits<int>::min(),
                                           std::numeric_limits<int>::min(),
                                           0}));

TEST_P(NumericLimitsSubtractTest, WorksWithNumericLimitsCorrectly) {
  auto params = GetParam();
  EXPECT_EQ(calculator.Subtract(params.a, params.b), params.expected);
}
