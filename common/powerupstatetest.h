#ifndef COMMON_POWERUPSTATETEST_H
#define COMMON_POWERUPSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PowerUpStateTest:
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PowerUpStateTest);
    CPPUNIT_TEST(getPowerUpWidth_widthIs1);
    CPPUNIT_TEST(getPowerUpHeight_heightIs1);
    CPPUNIT_TEST_SUITE_END();

private:
    void getPowerUpWidth_widthIs1();
    void getPowerUpHeight_heightIs1();

};
}

#endif
