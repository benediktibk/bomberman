#ifndef WALLSTATETEST_H
#define WALLSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class WallStateTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(WallStateTest);
	 CPPUNIT_TEST(setPosition_5And4_positionIs5And4);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void setPosition_5And4_positionIs5And4();
};
}

#endif
