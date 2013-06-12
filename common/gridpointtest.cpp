#include "gridpointtest.h"
#include "gridpoint.h"
#include <sstream>
#include <vector>

using namespace Common;

void GridPointTest::constructor_empty_xIs0()
{
	GridPoint point;

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, point.getX());
}

void GridPointTest::constructor_empty_yIs0()
{
	GridPoint point;

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, point.getY());
}

void GridPointTest::constructor_xIs4_xIs4()
{
	GridPoint point(4, 6);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, point.getX());
}

void GridPointTest::constructor_yIs6_yIs6()
{
	GridPoint point(4, 6);

	CPPUNIT_ASSERT_EQUAL((unsigned int)6, point.getY());
}

void GridPointTest::setX_5_xIs5()
{
	GridPoint point;

	point.setX(5);

	CPPUNIT_ASSERT_EQUAL((unsigned int)5, point.getX());
}

void GridPointTest::setY_4_yIs4()
{
	GridPoint point;

	point.setY(4);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, point.getY());
}

void GridPointTest::streamOperator_3And2_32()
{
	GridPoint point(3, 2);
	std::stringstream stream;

	stream << point;

	CPPUNIT_ASSERT_EQUAL(std::string("(3, 2)"), stream.str());
}

void GridPointTest::operatorMultiply_3And6With2_6And12()
{
	GridPoint point(3, 6);

	CPPUNIT_ASSERT_EQUAL(GridPoint(6, 12), point*2);
}

void GridPointTest::operatorDivide_3And6With3_1And2()
{
	GridPoint point(3, 6);

	CPPUNIT_ASSERT_EQUAL(GridPoint(1, 2), point/3);
}

void GridPointTest::operatorAdd_4And3To5And1_9And4()
{
	GridPoint pointOne(4, 3);
	GridPoint pointTwo(5, 1);

	GridPoint result = pointOne + pointTwo;

	CPPUNIT_ASSERT_EQUAL(GridPoint(9, 4), result);
}

void GridPointTest::operatorMinus_4And3From6And4_2And1()
{
	GridPoint pointOne(4, 3);
	GridPoint pointTwo(6, 4);

	GridPoint result = pointTwo - pointOne;

	CPPUNIT_ASSERT_EQUAL(GridPoint(2, 1), result);
}

void GridPointTest::constructor_pointWithNotExactPositions_correctPosition()
{
	GridPoint point(Point(3.96, 5.972));

	CPPUNIT_ASSERT_EQUAL(GridPoint(4, 6), point);
}

void GridPointTest::constructor_gridPoint3And4_3And4()
{
	GridPoint source(3, 4);

	GridPoint target(source);

	CPPUNIT_ASSERT_EQUAL(GridPoint(3, 4), target);
}

void GridPointTest::assignment_gridPoint3And4_3And4()
{
	GridPoint source(3, 4);
	GridPoint target;

	target = source;

	CPPUNIT_ASSERT_EQUAL(GridPoint(3, 4), target);
}

void GridPointTest::getCoveredGridPoints_pointat1point5and2_gridpoints()
{
    Point position(1.5,2.0);
    std::vector<GridPoint> coveredfields = GridPoint::getCoveredGridPoints(position);
    CPPUNIT_ASSERT_EQUAL((size_t)2, coveredfields.size());
}
