#include "powerupmaxbombstatetest.h"
#include "powerupmaxbombstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void PowerUpMaxBombStateTest::getPowerUpWidth_widthIs1()
{
    UniqueIdCreator id;
    PowerUpMaxBombState increaseMaxBomb(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, increaseMaxBomb.getWidth());
}

void PowerUpMaxBombStateTest::getPowerUpHeight_heightIs1()
{
    UniqueIdCreator id;
    PowerUpMaxBombState increaseMaxBomb(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, increaseMaxBomb.getHeight());
}
