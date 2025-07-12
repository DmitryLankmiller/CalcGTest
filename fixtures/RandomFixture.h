#pragma once

#include <gtest/gtest.h>
#include <random>

class RandomFixture : public virtual ::testing::Test {
protected:
  static std::mt19937 gen;
};
