#include "InMemoryHistory.h"
#include "SimpleCalculator.h"
#include <gtest/gtest.h>

namespace calc {

TEST(CalculatorTest, Add2And3IsEqualTo5) {
  // Arange
  InMemoryHistory history;
  SimpleCalculator calculator(history);

  // Act
  auto result = calculator.Add(2, 3);

  // Assert
  ASSERT_EQ(result, 5);
}

} // namespace calc