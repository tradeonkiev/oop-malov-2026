#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <vector>

#include "Circle.h"
#include "ICanvas.h"
#include "LineSegment.h"
#include "Point.h"
#include "Rectangle.h"
#include "ShapeUtils.h"
#include "Triangle.h"

struct MockCanvas : ICanvas
{
	MOCK_METHOD(void, DrawLine, (Point from, Point to, uint32_t lineColor), (override));
	MOCK_METHOD(void, FillPolygon, (std::vector<Point> points, uint32_t fillColor), (override));
	MOCK_METHOD(void, DrawCircle, (Point center, double radius, uint32_t lineColor), (override));
	MOCK_METHOD(void, FillCircle, (Point center, double radius, uint32_t fillColor), (override));
};

TEST(CPointTest, ConstructorAndToString)
{
	Point p1;
	EXPECT_DOUBLE_EQ(p1.x, 0.0);
	EXPECT_DOUBLE_EQ(p1.y, 0.0);

	Point p2(3.5, -2.1);
	EXPECT_DOUBLE_EQ(p2.x, 3.5);
	EXPECT_DOUBLE_EQ(p2.y, -2.1);
	EXPECT_EQ(p2.ToString(), "(3.50, -2.10)");
}

TEST(CLineSegmentTest, AreaAndPerimeter)
{
	LineSegment line(Point(0, 0), Point(3, 4), 0x000000);
	EXPECT_DOUBLE_EQ(line.GetArea(), 0.0);
	EXPECT_EQ(line.GetPerimeter(), 5.0);
}

TEST(CLineSegmentTest, ColorAndPoints)
{
	LineSegment line(Point(1, 2), Point(3, 4), 0xff0000);
	EXPECT_EQ(line.GetOutlineColor(), 0xff0000);
	EXPECT_DOUBLE_EQ(line.GetStartPoint().x, 1.0);
	EXPECT_DOUBLE_EQ(line.GetEndPoint().y, 4.0);
}

TEST(CLineSegmentTest, IsIShape)
{
	LineSegment line(Point(0, 0), Point(1, 0), 0x000000);
	IShape* shape = &line;
	EXPECT_DOUBLE_EQ(shape->GetArea(), 0.0);
}

TEST(CTriangleTest, AreaAndPerimeter)
{
	Triangle t(Point(0, 0), Point(3, 0), Point(0, 4), 0x000000, 0xffffff);
	EXPECT_EQ(t.GetArea(), 6.0);
	EXPECT_EQ(t.GetPerimeter(), 12.0);
}

TEST(CTriangleTest, ColorsAndVertices)
{
	Triangle t(Point(1, 2), Point(3, 4), Point(5, 6), 0xaabbcc, 0x112233);
	EXPECT_EQ(t.GetOutlineColor(), 0xaabbcc);
	EXPECT_EQ(t.GetFillColor(), 0x112233u);
	EXPECT_DOUBLE_EQ(t.GetVertex1().x, 1.0);
	EXPECT_DOUBLE_EQ(t.GetVertex2().y, 4.0);
	EXPECT_DOUBLE_EQ(t.GetVertex3().x, 5.0);
}

TEST(CTriangleTest, DegenerateTriangle)
{
	Triangle t(Point(0, 0), Point(1, 1), Point(2, 2), 0, 0);
	EXPECT_EQ(t.GetArea(), 0.0);
}

TEST(CRectangleTest, AreaAndPerimeter)
{
	Rectangle r(Point(0, 0), 10, 5, 0, 0);
	EXPECT_DOUBLE_EQ(r.GetArea(), 50.0);
	EXPECT_DOUBLE_EQ(r.GetPerimeter(), 30.0);
}

TEST(CRectangleTest, ColorsAndGeometry)
{
	Rectangle r(Point(10, 20), 30, 40, 0xff0000, 0x00ff00);
	EXPECT_EQ(r.GetOutlineColor(), 0xff0000);
	EXPECT_EQ(r.GetFillColor(), 0x00ff00);
	EXPECT_DOUBLE_EQ(r.GetLeftTop().x, 10.0);
	EXPECT_DOUBLE_EQ(r.GetRightBottom().y, 60.0);
	EXPECT_DOUBLE_EQ(r.GetWidth(), 30.0);
	EXPECT_DOUBLE_EQ(r.GetHeight(), 40.0);
}

TEST(CCircleTest, AreaAndPerimeter)
{
	Circle c(Point(0, 0), 5, 0, 0);
	EXPECT_EQ(c.GetArea(), M_PI * 25.0);
	EXPECT_EQ(c.GetPerimeter(), 2.0 * M_PI * 5.0);
}

TEST(CCircleTest, ColorsAndGeometry)
{
	Circle c(Point(3, 4), -7.5, 0xabcdef, 0x123456);
	EXPECT_EQ(c.GetOutlineColor(), 0xabcdef);
	EXPECT_EQ(c.GetFillColor(), 0x123456);
	EXPECT_DOUBLE_EQ(c.GetCenter().x, 3.0);
	EXPECT_DOUBLE_EQ(c.GetRadius(), 7.5);
}

TEST(ColorUtilsTest, ParseAndFormat)
{
	EXPECT_EQ(ParseColor("ff0000"), 0xff0000);
	EXPECT_EQ(ParseColor("000000"), 0x000000);
	EXPECT_EQ(ColorToString(0xff0000), "ff0000");
	EXPECT_EQ(ColorToString(0x000abc), "000abc");
}

TEST(ParseShapeTest, AllTypes)
{
	auto rect = ParseShape("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00");
	ASSERT_NE(rect, nullptr);
	EXPECT_EQ(rect->GetArea(), 30.7 * 40.4);

	auto circle = ParseShape("circle 5 10 3 aaaaaa bbbbbb");
	ASSERT_NE(circle, nullptr);
	EXPECT_EQ(circle->GetArea(), M_PI * 9.0);

	auto tri = ParseShape("triangle 0 0 3 0 0 4 000000 ffffff");
	ASSERT_NE(tri, nullptr);
	EXPECT_EQ(tri->GetArea(), 6.0);

	auto line = ParseShape("line 0 0 3 4 000000");
	ASSERT_NE(line, nullptr);
	EXPECT_DOUBLE_EQ(line->GetArea(), 0.0);
}

TEST(ParseShapeTest, InvalidInput)
{
	EXPECT_EQ(ParseShape("hexagon 1 2 3"), nullptr);
	EXPECT_EQ(ParseShape(""), nullptr);
	EXPECT_EQ(ParseShape("rectangle 10 20"), nullptr);
}

TEST(ReadShapesTest, EmptyInput)
{
	std::istringstream input("");
	auto shapes = ReadShapes(input);
	EXPECT_TRUE(shapes.empty());
}

TEST(FindShapesTest, MaxSAndMinP)
{
	std::istringstream input(
		"rectangle 0 0 10 5 ff0000 00ff00\n"
		"circle 0 0 3 aaaaaa bbbbbb\n"
		"triangle 0 0 3 0 0 4 000000 ffffff\n");
	auto shapes = ReadShapes(input);

	IShape* maxArea = FindMaxAreaShape(shapes);
	ASSERT_NE(maxArea, nullptr);
	EXPECT_EQ(maxArea->GetArea(), 50.0);

	IShape* minPer = FindMinPerimeterShape(shapes);
	ASSERT_NE(minPer, nullptr);
	EXPECT_EQ(minPer->GetPerimeter(), 12.0);
}

TEST(FindShapesTest, EmptyV)
{
	std::vector<std::unique_ptr<IShape>> empty;
	EXPECT_EQ(FindMaxAreaShape(empty), nullptr);
	EXPECT_EQ(FindMinPerimeterShape(empty), nullptr);
}

TEST(PrintShapeInfoTest, ValidAndInvalid)
{
	Rectangle r(Point(0, 0), 10, 5, 0xff0000, 0x00ff00);
	std::ostringstream oss1;
	PrintShapeInfo(oss1, &r);

	PrintShapeInfo(std::cout, &r);
	EXPECT_NE(oss1.str().find("ff0000"), std::string::npos);
	EXPECT_NE(oss1.str().find("00ff00"), std::string::npos);

	LineSegment l(Point(0, 0), Point(3, 4), 0xaabbcc);
	std::ostringstream oss2;
	PrintShapeInfo(oss2, &l);
	EXPECT_NE(oss2.str().find("aabbcc"), std::string::npos);
	EXPECT_EQ(oss2.str().find("Fill"), std::string::npos);
}

TEST(LineSegmentDrawTest, OneLine)
{
	MockCanvas canvas;
	LineSegment line(Point(0, 0), Point(10, 20), 0xff0000);

	EXPECT_CALL(canvas, DrawLine(::testing::_, ::testing::_, 0xff0000)).Times(1);

	line.Draw(canvas);
}

TEST(TriangleDrawTest, FillAndThreeLines)
{
	MockCanvas canvas;
	Triangle tri(Point(0, 0), Point(10, 0), Point(5, 8), 0xff0000, 0x00ff00);

	EXPECT_CALL(canvas, FillPolygon(::testing::_, 0x00ff00)).Times(1);
	EXPECT_CALL(canvas, DrawLine(::testing::_, ::testing::_, 0xff0000)).Times(3);

	tri.Draw(canvas);
}

TEST(RectangleDrawTest, FillAndFourLines)
{
	MockCanvas canvas;
	Rectangle rect(Point(10, 20), 30, 40, 0xff0000, 0x00ff00);

	EXPECT_CALL(canvas, FillPolygon(::testing::_, 0x00ff00)).Times(1);
	EXPECT_CALL(canvas, DrawLine(::testing::_, ::testing::_, 0xff0000)).Times(4);

	rect.Draw(canvas);
}

TEST(CircleDrawTest, FillAndOutline)
{
	MockCanvas canvas;
	Circle circle(Point(100, 200), 50, 0xff0000, 0x00ff00);

	EXPECT_CALL(canvas, FillCircle(::testing::_, 50, 0x00ff00)).Times(1);
	EXPECT_CALL(canvas, DrawCircle(::testing::_, 50, 0xff0000)).Times(1);

	circle.Draw(canvas);
}