#ifndef COMMON_POWERUPTEST_H
#define COMMON_POWERUPTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PowerUpTest:
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PowerUpTest);
    CPPUNIT_TEST(getPowerUpWidth_widthIs1);
    CPPUNIT_TEST(getPowerUpHeight_heightIs1);
    CPPUNIT_TEST_SUITE_END();

private:
    void getPowerUpWidth_widthIs1();
    void getPowerUpHeight_heightIs1();

};
}

#endif // POWERUPTEST_H
