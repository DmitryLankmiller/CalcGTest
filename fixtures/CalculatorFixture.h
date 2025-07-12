#pragma once

#include "HistoryMockFixture.h"
#include "calculator/SimpleCalculator.h"
#include <gtest/gtest.h>

class CalculatorFixture : public virtual HistoryMockFixture {
protected:
  calc::SimpleCalculator calculator{historyMock};

  void SetUp() override { HistoryMockFixture::SetUp(); }
};
