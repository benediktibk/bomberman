#include "poweruptest.h"
#include "powerup.h"
#include "uniqueidcreator.h"

using namespace Common;

void PowerUpTest::getPowerUpWidth_widthIs1()
{
    UniqueIdCreator id;
    PowerUp power(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, power.getWidth());
}

void PowerUpTest::getPowerUpHeight_heightIs1()
{
    UniqueIdCreator id;
    PowerUp power(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, power.getHeight());
}
