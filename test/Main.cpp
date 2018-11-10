#include "./Config.h"
#include <stdio.h>
#include "gtest/gtest.h"


class MemoryChecker
  : public testing::EmptyTestEventListener
{
public:
  virtual void OnTestStart(const ::testing::TestInfo& test_info) override {
    memset(&memory_state, 0, sizeof(memory_state));
    _CrtMemCheckpoint(&memory_state);
  }

  // Called after a test ends.
  virtual void OnTestEnd(const ::testing::TestInfo& test_info) override {
    _CrtMemState memory_state_after_test = { 0 };
    _CrtMemCheckpoint(&memory_state_after_test);
    _CrtMemState memory_state_output = { 0 };
    if (_CrtMemDifference(&memory_state_output, &memory_state, &memory_state_after_test))
      _CrtMemDumpStatistics(&memory_state_output);
    _CrtMemDumpAllObjectsSince(&memory_state);
  }

private:
  _CrtMemState memory_state;
};

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);

  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();
  // Adds a listener to the end.  googletest takes the ownership.
  listeners.Append(new MemoryChecker);

  return RUN_ALL_TESTS();
}
