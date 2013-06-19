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
    CPPUNIT_TEST(getRandomPowerUpType_1000Times_PowerUpTypeNoneCountIsInRange);
	CPPUNIT_TEST(getRandomPowerUpType_1000Times_PowerUpTypeMaxBombIsInRange);
	CPPUNIT_TEST(getRandomPowerUpType_1000Times_PowerUpTypeMaxVelocityIsInRange);
	CPPUNIT_TEST(getRandomPowerUpType_1000Times_PowerUpTypeMaxBombRangeIsInRange);
    CPPUNIT_TEST_SUITE_END();

private:
    void getRandomPowerUpType_PowerUpType();
    void getRandomPowerUpType_1000Times_PowerUpTypeNoneCountIsInRange();
	void getRandomPowerUpType_1000Times_PowerUpTypeMaxBombIsInRange();
	void getRandomPowerUpType_1000Times_PowerUpTypeMaxVelocityIsInRange();
	void getRandomPowerUpType_1000Times_PowerUpTypeMaxBombRangeIsInRange();

};
}

#endif
