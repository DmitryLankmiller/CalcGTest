#pragma once

#include "IHistoryMock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class HistoryMockFixture : public virtual ::testing::Test {
protected:
  testing::NiceMock<IHistoryMock> historyMock;

  void SetUp() override {
    ON_CALL(historyMock, AddEntry(::testing::_))
        .WillByDefault(::testing::Return());
  }
};
