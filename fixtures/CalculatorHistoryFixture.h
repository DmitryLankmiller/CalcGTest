#pragma once

#include "IHistoryMock.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>

class CalculatorHistoryFixture : public virtual ::testing::Test {
protected:
  IHistoryMock historyMock;
  calc::SimpleCalculator calculator{historyMock};
};
