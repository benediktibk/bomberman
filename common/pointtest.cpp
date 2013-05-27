#include "pointtest.h"
#include "point.h"
#include <sstream>

using namespace Common;

void PointTest::constructor_empty_xIs0()
{
	Point point;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, point.getX(), 0.0001);
}

void PointTest::constructor_empty_yIs0()
{
	Point point;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, point.getY(), 0.0001);
}

void PointTest::constructor_xIs4_xIs4()
{
	Point point(4, 6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, point.getX(), 0.0001);
}

void PointTest::constructor_yIs6_yIs6()
{
	Point point(4, 6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, point.getY(), 0.0001);
}

void PointTest::setX_5_xIs5()
{
	Point point;

	point.setX(5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, point.getX(), 0.0001);
}

void PointTest::setY_4_yIs4()
{
	Point point;

	point.setY(4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, point.getY(), 0.0001);
}

void PointTest::streamOperator_3And2_32()
{
	Point point(3, 2);
	std::stringstream stream;

	stream << point;

	CPPUNIT_ASSERT_EQUAL(std::string("(3, 2)"), stream.str());
}

void PointTest::operatorMultiply_3And6With2_6And12()
{
	Point point(3, 6);

	CPPUNIT_ASSERT_EQUAL(Point(6, 12), point*2);
}

void PointTest::operatorDivide_3And6With3_1And2()
{
	Point point(3, 6);

	CPPUNIT_ASSERT_EQUAL(Point(1, 2), point/3);
}
