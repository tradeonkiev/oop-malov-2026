#include <gtest/gtest.h>
#include <sstream>
#include "urlparser.h"

TEST(UrlInfo, SimpleHttp) {
    UrlInfo info("http://example.com");
    EXPECT_EQ(info.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(info.GetHost(), "example.com");
    EXPECT_EQ(info.GetPort(), 80);
    EXPECT_EQ(info.GetDocument(), "");
    EXPECT_EQ(info.GetOriginalUrl(), "http://example.com");
}

TEST(UrlInfo, WithPort) {
    UrlInfo info("http://example.com:8080/index.html");
    EXPECT_EQ(info.GetHost(), "example.com");
    EXPECT_EQ(info.GetPort(), 8080);
    EXPECT_EQ(info.GetDocument(), "index.html");
}

TEST(UrlInfo, HttpsMixedCase) {
    UrlInfo info("HtTpS://secure.site.com/page");
    EXPECT_EQ(info.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(info.GetPort(), 443);
}

TEST(UrlInfo, FtpDefaultPort) {
    UrlInfo info("ftp://file.com/pub/file.txt");
    EXPECT_EQ(info.GetProtocol(), Protocol::FTP);
    EXPECT_EQ(info.GetPort(), 21);
    EXPECT_EQ(info.GetDocument(), "pub/file.txt");
}

TEST(UrlInfo, ComplexDocument) {
    UrlInfo info("http://www.mysite.com/docs/document1.html?page=30&lang=en");
    EXPECT_EQ(info.GetHost(), "www.mysite.com");
    EXPECT_EQ(info.GetDocument(), "docs/document1.html?page=30&lang=en");
}

TEST(UrlInfo, OriginalUrlPreserved) {
    std::string url = "HtTp://example.com:8080/index.html";
    UrlInfo info(url);
    EXPECT_EQ(info.GetOriginalUrl(), url);
}

TEST(UrlInfo, PortOnly) {
    UrlInfo info("http://example.com:3000");
    EXPECT_EQ(info.GetPort(), 3000);
    EXPECT_EQ(info.GetDocument(), "");
}

TEST(UrlInfo, TrailingSlash) {
    UrlInfo info("http://example.com/");
    EXPECT_EQ(info.GetDocument(), "");
}

TEST(UrlInfo, InvalidProtocolThrows) {
    EXPECT_THROW(UrlInfo("htp://example.com"), std::invalid_argument);
}

TEST(UrlInfo, MissingHostThrows) {
    EXPECT_THROW(UrlInfo("http:///document"), std::invalid_argument);
}

TEST(UrlInfo, PortZeroThrows) {
    EXPECT_THROW(UrlInfo("http://Pen.s:0/page"), std::out_of_range);
}

TEST(UrlInfo, PortTooLargeThrows) {
    EXPECT_THROW(UrlInfo("http://example.com:65536/page"), std::out_of_range);
}

TEST(UrlInfo, EmptyStringThrows) {
    EXPECT_THROW(UrlInfo(""), std::invalid_argument);
}

TEST(UrlInfo, NoProtocolThrows) {
    EXPECT_THROW(UrlInfo("example.com"), std::invalid_argument);
}

TEST(UrlInfo, PrintFormatsCorrectly) {
    UrlInfo info("http://example.com/index.html");
    std::ostringstream output;
    info.Print(output);
    EXPECT_EQ(output.str(),
        "http://example.com/index.html\n"
        "HOST: example.com\n"
        "PORT: 80\n"
        "DOC: index.html\n");
}