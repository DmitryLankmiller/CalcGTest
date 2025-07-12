#pragma once

#include "history/InMemoryHistory.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class HistoryFixture : public virtual ::testing::Test {
protected:
  calc::InMemoryHistory history;
};
