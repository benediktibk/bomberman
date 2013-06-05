#include "powerupgeneratortest.h"
#include "powerupgenerator.h"

using namespace Common;

void PowerUpGeneratorTest::getRandomPowerUpType_PowerUpType()
{
    PowerUpGenerator generator;

    CPPUNIT_ASSERT_EQUAL(true , generator.getRandomPowerUpType() > -1);
}
