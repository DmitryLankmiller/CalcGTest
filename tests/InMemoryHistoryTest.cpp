#include "HistoryFixture.h"
#include <gtest/gtest.h>
#include <random>
#include <string>

const std::string CHARACTERS = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";

std::string generateRandomString(size_t length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

  std::string randomString;
  randomString.reserve(length);

  for (size_t i = 0; i < length; i++) {
    randomString += CHARACTERS[distribution(gen)];
  }

  return randomString;
}

TEST_F(HistoryFixture, AddEntry2Plus3Equal5) {
  const std::string operation{"2 + 3 = 5"};
  history.AddEntry(operation);

  const auto gotOperation = history.GetLastOperations(1).back();

  ASSERT_EQ(operation, gotOperation);
}

TEST_F(HistoryFixture, GetMoreThanCountOperations) {
  const size_t count = 5;

  for (size_t i = 0; i < count; i++) {
    history.AddEntry(generateRandomString(10));
  }

  const auto operations = history.GetLastOperations(2 * count);

  ASSERT_EQ(count, operations.size());
}

TEST_F(HistoryFixture, CheckRandomOperations) {
  const size_t operationsCount = 10;
  std::vector<std::string> operations;
  operations.reserve(operationsCount);

  for (size_t i = 0; i < operationsCount; i++) {
    const std::string op = generateRandomString(10);
    operations.push_back(op);
    history.AddEntry(op);
  }

  const auto gotOperations = history.GetLastOperations(operationsCount);
  EXPECT_EQ(operations, gotOperations);
}
