#include "powerupstatetest.h"
#include "powerupstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void PowerUpStateTest::getPowerUpWidth_widthIs1()
{
    UniqueIdCreator id;
    PowerUpState power(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, power.getWidth());
}

void PowerUpStateTest::getPowerUpHeight_heightIs1()
{
    UniqueIdCreator id;
    PowerUpState power(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, power.getHeight());
}
