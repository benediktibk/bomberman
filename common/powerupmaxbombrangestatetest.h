#ifndef COMMON_POWERUPMAXBOMBRANGESTATETEST_H
#define COMMON_POWERUPMAXBOMBRANGESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PowerUpMaxBombRangeStateTest :
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PowerUpMaxVelocityStateTest);
    CPPUNIT_TEST(modifyPlayer_maxSpeed_7);
    CPPUNIT_TEST(modifyPlayer_baseClass_maxSpeed_7);
    CPPUNIT_TEST_SUITE_END();

private:
    void modifyPlayer_maxSpeed_7();
    void modifyPlayer_baseClass_maxSpeed_7();

};
}




#endif
