#include "../Config.h"
#include "parser/MiscParser.h"
#include "gtest/gtest.h"

using namespace tinysvg;
using namespace std;


TEST(MiscParserTest, ParseNumericList) {
  pair<bool, vector<SvgLength>> result = ParseNumericList("");
  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second.size(), 0);

  result = ParseNumericList("fucker");
  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second.size(), 0);

  result = ParseNumericList("5");
  EXPECT_TRUE(result.first);
  ASSERT_EQ(result.second.size(), 1) << result.second.size();
  EXPECT_DOUBLE_EQ(result.second[0], 5.0) << result.second[0];

  result = ParseNumericList("12, ");
  EXPECT_FALSE(result.first);
  ASSERT_EQ(result.second.size(), 1) << result.second.size();
  EXPECT_DOUBLE_EQ(result.second[0], 12.0) << result.second[0];

  result = ParseNumericList("9.756 , -1655498, f");
  EXPECT_FALSE(result.first);
  ASSERT_EQ(result.second.size(), 2) << result.second.size();
  EXPECT_DOUBLE_EQ(result.second[0], 9.756) << result.second[0];
  EXPECT_DOUBLE_EQ(result.second[1], -1655498) << result.second[1];

  result = ParseNumericList("   2316.165, 1235 ,    -1322654,708123.05246   ");
  EXPECT_TRUE(result.first);
  ASSERT_EQ(result.second.size(), 4) << result.second.size();
  EXPECT_DOUBLE_EQ(result.second[0], 2316.165) << result.second[0];
  EXPECT_DOUBLE_EQ(result.second[1], 1235) << result.second[1];
  EXPECT_DOUBLE_EQ(result.second[2], -1322654) << result.second[2];
  EXPECT_DOUBLE_EQ(result.second[3], 708123.05246) << result.second[3];
}