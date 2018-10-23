#include <gtest/gtest.h>
#include <common/DomString.h>

using namespace tinysvg;
using namespace std;

TEST(DomStringTest, EmptyStringTest)
{
  tinysvg::DomString target("");
  ASSERT_EQ(target.Split(u8"good").size(), 1);
  EXPECT_EQ(target.Split(u8"good")[0], DomString(""));
}

TEST(DomStringTest, EmptySplitterTest)
{
  tinysvg::DomString target(u8"abc");
  ASSERT_EQ(target.Split("").size(), 3) << target.Split("").size();
  EXPECT_EQ(target.Split("")[0], DomString(u8"a")) << target.Split("")[0];
  EXPECT_EQ(target.Split("")[1], DomString(u8"b")) << target.Split("")[1];
  EXPECT_EQ(target.Split("")[2], DomString(u8"c")) << target.Split("")[2];
}

TEST(TestTest, Fucker)
{
  tinysvg::DomString target(u8"abcabc");

  vector<DomString> result = target.Split(u8"bc");

  ASSERT_EQ(result.size(), 3);
  EXPECT_TRUE(result[0] == DomString(u8"a")) << result[0] << DomString("");
  EXPECT_TRUE(result[1] == DomString(u8"a")) << result[1];
  EXPECT_TRUE(result[2] == "") << result[2];
}