#include "../Config.h"
#include "gtest/gtest.h"
#include "svg/SvgDocument.h"

using namespace tinysvg;


TEST(SvgDocumentParserTest, SimpleDocument) {
  const char document[] = u8"<svg viewBox=\"0 0 300 100\" xmlns=\"http://www.w3.org/2000/svg\"></svg>";
  SvgDocument doc;
  bool parse_succeeded = doc.Parse(document);
  ASSERT_TRUE(parse_succeeded);
  optional<NodeDelegate<SvgSvg>> maybe_root_delegate = doc.Root();
  ASSERT_TRUE(maybe_root_delegate.has_value());
  SvgSvg::SvgViewBox vb = maybe_root_delegate.value().Value().ViewBox().value();
  ASSERT_TRUE(vb.x.has_value());
  ASSERT_TRUE(vb.y.has_value());
  ASSERT_TRUE(vb.width.has_value());
  ASSERT_TRUE(vb.height.has_value());
  EXPECT_DOUBLE_EQ(vb.x.value(), 0);
  EXPECT_DOUBLE_EQ(vb.y.value(), 0);
  EXPECT_DOUBLE_EQ(vb.width.value(), 300);
  EXPECT_DOUBLE_EQ(vb.height.value(), 100);
}
