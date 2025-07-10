#pragma once

#include "IHistory.h"
#include <gmock/gmock.h>
#include <string>
#include <vector>

class IHistoryMock : public calc::IHistory {
public:
  MOCK_METHOD(void, AddEntry, (const std::string &), (override));
  MOCK_METHOD((std::vector<std::string>), GetLastOperations, (size_t),
              (const override));
};
