#include "IHistoryMock.h"
#include "SimpleCalculator.h"
#include <gtest/gtest.h>

TEST(CalculatorTest, Add2And3IsEqualTo5) {
  // Arange
  IHistoryMock history;
  calc::SimpleCalculator calculator(history);

  // Act
  auto result = calculator.Add(2, 3);

  // Assert
  ASSERT_EQ(result, 5);
}
