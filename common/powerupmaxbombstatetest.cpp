#include "powerupmaxbombstatetest.h"
#include "powerupmaxbombstate.h"
#include "uniqueidcreator.h"
#include "playerstate.h"

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

void PowerUpMaxBombStateTest::modifyPlayer_maxBombIs2()
{
    UniqueIdCreator id;
    UniqueIdCreator idPlayer;
    PowerUpMaxBombState increaseMaxBomb(id, Point());
    PlayerState player(idPlayer);

    increaseMaxBomb.modifyPlayer(player);

    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(2), player.getMaxBombs());
}
