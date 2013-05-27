#ifndef COMMON_POINTTEST_H
#define COMMON_POINTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PointTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(PointTest);
	 CPPUNIT_TEST(constructor_empty_xIs0);
	 CPPUNIT_TEST(constructor_empty_yIs0);
	 CPPUNIT_TEST(constructor_xIs4_xIs4);
	 CPPUNIT_TEST(constructor_yIs6_yIs6);
	 CPPUNIT_TEST(setX_5_xIs5);
	 CPPUNIT_TEST(setY_4_yIs4);
	 CPPUNIT_TEST(streamOperator_3And2_32);
	 CPPUNIT_TEST(operatorMultiply_3And6With2_6And12);
	 CPPUNIT_TEST(operatorDivide_3And6With3_1And2);
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
};
}

#endif