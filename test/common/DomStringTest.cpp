#include "gtest/gtest.h"
#include "common/DomString.h"

using namespace tinysvg;
using namespace std;

TEST(DomStringTest, EmptyStringTest)
{
  tinysvg::DomString target(u8"");
  ASSERT_EQ(target.Split(u8"good").size(), 1);
  EXPECT_EQ(target.Split(u8"good")[0], DomString(u8""));
}

TEST(DomStringTest, EmptySplitterTest)
{
  tinysvg::DomString target(u8"abc");
  ASSERT_EQ(target.Split(u8"").size(), 3) << target.Split(u8"").size();
  EXPECT_EQ(target.Split(u8"")[0], DomString(u8"a")) << target.Split(u8"")[0];
  EXPECT_EQ(target.Split(u8"")[1], DomString(u8"b")) << target.Split(u8"")[1];
  EXPECT_EQ(target.Split(u8"")[2], DomString(u8"c")) << target.Split(u8"")[2];
}

TEST(TestTest, Fucker)
{
  tinysvg::DomString target(u8"abcabc");

  vector<DomString> result = target.Split(u8"bc");

  ASSERT_EQ(result.size(), 3);
  EXPECT_TRUE(result[0] == DomString(u8"a")) << result[0] << DomString(u8"");
  EXPECT_TRUE(result[1] == DomString(u8"a")) << result[1];
  EXPECT_TRUE(result[2] == u8"") << result[2];
}