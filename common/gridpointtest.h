#ifndef COMMON_GRIDPOINTTEST_H
#define COMMON_GRIDPOINTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class GridPointTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(GridPointTest);
	 CPPUNIT_TEST(constructor_empty_xIs0);
	 CPPUNIT_TEST(constructor_empty_yIs0);
	 CPPUNIT_TEST(constructor_xIs4_xIs4);
	 CPPUNIT_TEST(constructor_yIs6_yIs6);
	 CPPUNIT_TEST(setX_5_xIs5);
	 CPPUNIT_TEST(setY_4_yIs4);
	 CPPUNIT_TEST(streamOperator_3And2_32);
	 CPPUNIT_TEST(operatorMultiply_3And6With2_6And12);
	 CPPUNIT_TEST(operatorDivide_3And6With3_1And2);
	 CPPUNIT_TEST(operatorAdd_4And3To5And1_9And4);
	 CPPUNIT_TEST(operatorMinus_4And3From6And4_2And1);
	 CPPUNIT_TEST(constructor_pointWithNotExactPositions_correctPosition);
	 CPPUNIT_TEST(constructor_gridPoint3And4_3And4);
	 CPPUNIT_TEST(assignment_gridPoint3And4_3And4);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_empty_xIs0();
	 void constructor_empty_yIs0();
	 void constructor_xIs4_xIs4();
	 void constructor_yIs6_yIs6();
	 void setX_5_xIs5();
	 void setY_4_yIs4();
	 void streamOperator_3And2_32();
	 void operatorMultiply_3And6With2_6And12();
	 void operatorDivide_3And6With3_1And2();
	 void operatorAdd_4And3To5And1_9And4();
	 void operatorMinus_4And3From6And4_2And1();
	 void constructor_pointWithNotExactPositions_correctPosition();
	 void constructor_gridPoint3And4_3And4();
	 void assignment_gridPoint3And4_3And4();
};
}

#endif
