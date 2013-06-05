#ifndef COMMON_POWERUPGENERATORTEST_H
#define COMMON_POWERUPGENERATORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class PowerUpGeneratorTest :
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PowerUpGeneratorTest);
    CPPUNIT_TEST(getRandomPowerUpType_PowerUpType);
    CPPUNIT_TEST_SUITE_END();

private:
    void getRandomPowerUpType_PowerUpType();

};
}

#endif
