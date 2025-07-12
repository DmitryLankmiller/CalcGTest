#pragma once

#include "CalculatorFixture.h"
#include "RandomFixture.h"
#include <gtest/gtest.h>

class CalculatorAndRandomFixture : public CalculatorFixture,
                                   public RandomFixture {
protected:
  void SetUp() override {
    CalculatorFixture::SetUp();
    RandomFixture::SetUp();
  }
};
