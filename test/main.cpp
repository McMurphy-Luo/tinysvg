#include <cstdio>
#include <gtest/gtest.h>

int main(int argc, char argv[]) {
  ASSERT_EQ(5, 4) << "good";
  printf("hello world");
  return 0;
}
