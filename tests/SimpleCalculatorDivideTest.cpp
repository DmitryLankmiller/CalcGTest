#include "CalculatorAndRandomFixture.h"
#include "CalculatorFixture.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>
#include <random>

TEST_F(CalculatorFixture, Divide3And2IsEqualTo1) {
  auto result = calculator.Divide(3, 2);

  ASSERT_EQ(result, 1);
}

TEST_F(CalculatorFixture, DivisionByZero) {
  EXPECT_THROW(calculator.Divide(5, 0), std::invalid_argument);
}

TEST_F(CalculatorAndRandomFixture, DivideWithZero) {
  ASSERT_EQ(calculator.Multiply(1, 5), 5);

  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    EXPECT_EQ(calculator.Divide(0, a), 0);
  }
}

TEST_F(CalculatorAndRandomFixture, DivideWithOne) {
  ASSERT_EQ(calculator.Multiply(1, 5), 5);

  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    EXPECT_EQ(calculator.Divide(a, 1), a);
  }
}

TEST_F(CalculatorAndRandomFixture, DivideRandoms) {
  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min() + 1,
                                          std::numeric_limits<int>::max());

  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    int b = dist(gen);
    auto result = a / b;
    EXPECT_EQ(calculator.Divide(a, b), result);
  }
}

struct DivideLimitsParams {
  int a;
  int b;
  int expected;
};

class NumericLimitsDivideTest
    : public CalculatorFixture,
      public ::testing::WithParamInterface<DivideLimitsParams> {};

INSTANTIATE_TEST_SUITE_P(
    Calc, NumericLimitsDivideTest,
    ::testing::Values(DivideLimitsParams{std::numeric_limits<int>::max(), 1,
                                         std::numeric_limits<int>::max()},
                      DivideLimitsParams{std::numeric_limits<int>::max(), -1,
                                         -std::numeric_limits<int>::max()},
                      DivideLimitsParams{std::numeric_limits<int>::max(),
                                         std::numeric_limits<int>::max(), 1},
                      DivideLimitsParams{std::numeric_limits<int>::max(),
                                         -std::numeric_limits<int>::max(), -1},
                      DivideLimitsParams{std::numeric_limits<int>::max(), 5,
                                         std::numeric_limits<int>::max() / 5},
                      DivideLimitsParams{std::numeric_limits<int>::min(), 1,
                                         std::numeric_limits<int>::min()},
                      DivideLimitsParams{std::numeric_limits<int>::min(),
                                         std::numeric_limits<int>::min(), 1},
                      DivideLimitsParams{std::numeric_limits<int>::min(), 5,
                                         std::numeric_limits<int>::min() / 5}));

TEST_P(NumericLimitsDivideTest, WorksWithNumericLimitsCorrectly) {
  auto params = GetParam();
  EXPECT_EQ(calculator.Divide(params.a, params.b), params.expected);
}
