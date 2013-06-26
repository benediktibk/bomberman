#ifndef COMMON_POWERUPMAXBOMBRANGESTATETEST_H
#define COMMON_POWERUPMAXBOMBRANGESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PowerUpMaxBombRangeStateTest :
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PowerUpMaxBombRangeStateTest);
    CPPUNIT_TEST(modifyPlayer_maxBombRange_2);
	CPPUNIT_TEST(modifyPlayer_baseClass_maxBombRangeIs2);
	CPPUNIT_TEST(getPowerUpType_isMaxBombRange);
    CPPUNIT_TEST_SUITE_END();

private:
    void modifyPlayer_maxBombRange_2();
	void modifyPlayer_baseClass_maxBombRangeIs2();
	void getPowerUpType_isMaxBombRange();

};
}




#endif
