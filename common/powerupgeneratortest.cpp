#include "powerupgeneratortest.h"
#include "powerupgenerator.h"

using namespace Common;

void PowerUpGeneratorTest::getRandomPowerUpType_PowerUpType()
{
	PowerUpGenerator generator;

	CPPUNIT_ASSERT_EQUAL(true , generator.getRandomPowerUpType() > -1);
}

void PowerUpGeneratorTest::getRandomPowerUpType_1000Times_PowerUpTypeNoneCountIsInRange()
{
	int counter = 0;
	PowerUpGenerator generator;

	for (int x = 0; x < 1000; ++x) {
		if (generator.getRandomPowerUpType() == PowerUpTypeNone)
			counter++;
	}

	CPPUNIT_ASSERT(counter > 700 && counter < 800);
}
