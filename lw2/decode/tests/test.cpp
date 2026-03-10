#include <gtest/gtest.h>
#include "decode.h"

TEST(HtmlDecode, DecodesQuot) {
    EXPECT_EQ(HtmlDecode("&quot;"), "\"");
}

TEST(HtmlDecode, DecodesApos) {
    EXPECT_EQ(HtmlDecode("&apos;"), "'");
}

TEST(HtmlDecode, DecodesAmp) {
    EXPECT_EQ(HtmlDecode("&amp;"), "&");
}

TEST(HtmlDecode, DecodesLt) {
    EXPECT_EQ(HtmlDecode("&lt;"), "<");
}

TEST(HtmlDecode, DecodesGt) {
    EXPECT_EQ(HtmlDecode("&gt;"), ">");
}

TEST(HtmlDecode, DecodesInsideText) {
    EXPECT_EQ(HtmlDecode("a &lt;b&gt; c"), "a <b> c");
}

TEST(HtmlDecode, DecodesMultipleEntities) {
    EXPECT_EQ(HtmlDecode("&lt;&amp;&gt;"), "<&>");
}

TEST(HtmlDecode, DecodesRealHtml) {
    EXPECT_EQ(HtmlDecode("&lt;div class=&quot;main&quot;&gt;"), "<div class=\"main\">");
}

TEST(HtmlDecode, EmptyString) {
    EXPECT_EQ(HtmlDecode(""), "");
}

TEST(HtmlDecode, NoEntities) {
    EXPECT_EQ(HtmlDecode("hello world"), "hello world");
}

TEST(HtmlDecode, LoneAmpersand) {
    EXPECT_EQ(HtmlDecode("a & b"), "a & b");
}

TEST(HtmlDecode, UnknownEntity) {
    EXPECT_EQ(HtmlDecode("&nbsp;"), "&nbsp;");
}

TEST(HtmlDecode, AmpersandAtEnd) {
    EXPECT_EQ(HtmlDecode("hello&"), "hello&");
}

TEST(HtmlDecode, DoubleEncoded) {
    EXPECT_EQ(HtmlDecode("&amp;lt;"), "&lt;");
}

TEST(HtmlDecode, RecursiveEncoded) {
    EXPECT_EQ(HtmlDecode("&amp;amp;"), "&amp;");
}