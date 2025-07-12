#include "CalculatorAndRandomFixture.h"
#include "CalculatorFixture.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>
#include <random>

TEST_F(CalculatorFixture, Multiply2And3IsEqualTo6) {
  auto result = calculator.Multiply(2, 3);

  ASSERT_EQ(result, 6);
}

TEST_F(CalculatorAndRandomFixture, MultiplyWithZero) {
  ASSERT_EQ(calculator.Multiply(1, 0), 0);

  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    EXPECT_EQ(calculator.Multiply(0, a), 0);
    EXPECT_EQ(calculator.Multiply(a, 0), 0);
  }
}

TEST_F(CalculatorAndRandomFixture, MultiplyWithOne) {
  ASSERT_EQ(calculator.Multiply(1, 5), 5);

  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    EXPECT_EQ(calculator.Multiply(1, a), a);
    EXPECT_EQ(calculator.Multiply(a, 1), a);
  }
}

TEST_F(CalculatorAndRandomFixture, MultipyRandom) {
  std::uniform_int_distribution<int> dist(-1000, 1000);

  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    int b = dist(gen);
    auto result = a * b;
    EXPECT_EQ(calculator.Multiply(a, b), result);
  }
}

TEST_F(CalculatorAndRandomFixture, MultipyOrderCheck) {
  std::uniform_int_distribution<int> dist(-1000, 1000);

  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    int b = dist(gen);
    auto result = a * b;
    EXPECT_EQ(calculator.Multiply(a, b), result);
    EXPECT_EQ(calculator.Multiply(b, a), result);
  }
}

struct MultiplyLimitsParams {
  int a;
  int b;
  int expected;
};

class NumericLimitsMultiplyTest
    : public CalculatorFixture,
      public ::testing::WithParamInterface<MultiplyLimitsParams> {};

INSTANTIATE_TEST_SUITE_P(
    Calc, NumericLimitsMultiplyTest,
    ::testing::Values(
        MultiplyLimitsParams{std::numeric_limits<int>::max(), 1,
                             std::numeric_limits<int>::max()},
        MultiplyLimitsParams{std::numeric_limits<int>::max(), 0, 0},
        MultiplyLimitsParams{std::numeric_limits<int>::max() / 3, 3,
                             std::numeric_limits<int>::max() / 3 * 3},
        MultiplyLimitsParams{std::numeric_limits<int>::min(), 1,
                             std::numeric_limits<int>::min()},
        MultiplyLimitsParams{std::numeric_limits<int>::min(), 0, 0},
        MultiplyLimitsParams{std::numeric_limits<int>::min() / 3, 3,
                             std::numeric_limits<int>::min() / 3 * 3}));

TEST_P(NumericLimitsMultiplyTest, WorksWithNumericLimitsCorrectly) {
  auto params = GetParam();
  EXPECT_EQ(calculator.Multiply(params.a, params.b), params.expected);
}
