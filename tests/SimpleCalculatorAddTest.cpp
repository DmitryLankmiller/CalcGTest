#include "CalculatorAndRandomFixture.h"
#include "CalculatorFixture.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>
#include <random>

TEST_F(CalculatorFixture, Add2And3IsEqualTo5) {
  auto result = calculator.Add(2, 3);

  ASSERT_EQ(result, 5);
}

TEST_F(CalculatorAndRandomFixture, AddZero) {
  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    EXPECT_EQ(calculator.Add(0, a), a);
    EXPECT_EQ(calculator.Add(a, 0), a);
  }
}

TEST_F(CalculatorAndRandomFixture, AddRandoms) {
  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min() / 2,
                                          std::numeric_limits<int>::max() / 2);

  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    int b = dist(gen);
    auto result = a + b;
    EXPECT_EQ(calculator.Add(a, b), result);
  }
}

TEST_F(CalculatorAndRandomFixture, AddOrderCheck) {
  std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min() / 2,
                                          std::numeric_limits<int>::max() / 2);

  for (size_t i = 0; i < 10; i++) {
    int a = dist(gen);
    int b = dist(gen);
    auto result = a + b;
    EXPECT_EQ(calculator.Add(a, b), result);
    EXPECT_EQ(calculator.Add(b, a), result);
  }
}

struct AddLimitsParams {
  int a;
  int b;
  int expected;
};

class NumericLimitsAddTest
    : public CalculatorFixture,
      public ::testing::WithParamInterface<AddLimitsParams> {};

INSTANTIATE_TEST_SUITE_P(
    Calc, NumericLimitsAddTest,
    ::testing::Values(AddLimitsParams{std::numeric_limits<int>::max(), -1,
                                      std::numeric_limits<int>::max() - 1},
                      AddLimitsParams{std::numeric_limits<int>::max(), 0,
                                      std::numeric_limits<int>::max()},
                      AddLimitsParams{std::numeric_limits<int>::max() - 1, 1,
                                      std::numeric_limits<int>::max()},
                      AddLimitsParams{std::numeric_limits<int>::max(),
                                      -std::numeric_limits<int>::max(), 0},
                      AddLimitsParams{std::numeric_limits<int>::min(), 1,
                                      std::numeric_limits<int>::min() + 1},
                      AddLimitsParams{std::numeric_limits<int>::min(), 0,
                                      std::numeric_limits<int>::min()},
                      AddLimitsParams{std::numeric_limits<int>::min() + 1, -1,
                                      std::numeric_limits<int>::min()}));

TEST_P(NumericLimitsAddTest, WorksWithNumericLimitsCorrectly) {
  auto params = GetParam();
  EXPECT_EQ(calculator.Add(params.a, params.b), params.expected);
}
