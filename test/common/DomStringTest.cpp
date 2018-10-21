#include <gtest/gtest.h>
#include <common/DomString.h>

using namespace tinysvg;
using namespace std;

TEST(TestTest, Fucker) {
  tinysvg::DomString target("abcabc");

  vector<DomString> result = target.Split("bc");


  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result[0] == DomString("a")) << result[0] << DomString("");
  EXPECT_TRUE(result[1] == DomString("a")) << result[1];
  EXPECT_TRUE(result[2] == "") << result[2];
  EXPECT_EQ(1, 1);
}