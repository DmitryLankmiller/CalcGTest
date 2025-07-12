#include "CalculatorFixture.h"
#include "CalculatorHistoryFixture.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>
#include <random>

TEST_F(CalculatorHistoryFixture, IntegrationOnAdd2And3IsEqualTo5) {
  EXPECT_CALL(historyMock, AddEntry("2 + 3 = 5"));

  calculator.Add(2, 3);
}

TEST_F(CalculatorHistoryFixture, IntegrationOnMultiply2And3IsEqualTo6) {
  EXPECT_CALL(historyMock, AddEntry("2 * 3 = 6"));

  calculator.Multiply(2, 3);
}

TEST_F(CalculatorHistoryFixture, IntegrationOnDivide2And3IsEqualTo0) {
  EXPECT_CALL(historyMock, AddEntry("2 / 3 = 0"));

  calculator.Divide(2, 3);
}

TEST_F(CalculatorHistoryFixture, IntegrationOnSubtract2And3IsEqualToMinus1) {
  EXPECT_CALL(historyMock, AddEntry("2 - 3 = -1"));

  calculator.Subtract(2, 3);
}
