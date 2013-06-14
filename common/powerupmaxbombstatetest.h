#ifndef COMMON_POWERUPMAXBOMBSTATETEST_H
#define COMMON_POWERUPMAXBOMBSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PowerUpMaxBombStateTest :
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PowerUpMaxBombStateTest);
    CPPUNIT_TEST(getPowerUpWidth_widthIs1);
    CPPUNIT_TEST(getPowerUpHeight_heightIs1);
    CPPUNIT_TEST(modifyPlayer_maxBombIs2);
    CPPUNIT_TEST(modifyPlayer_baseClass_maxBombIs2);
    CPPUNIT_TEST_SUITE_END();

private:
    void getPowerUpWidth_widthIs1();
    void getPowerUpHeight_heightIs1();
    void modifyPlayer_maxBombIs2();
    void modifyPlayer_baseClass_maxBombIs2();

};
}

#endif
