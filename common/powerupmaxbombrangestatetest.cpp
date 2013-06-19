#include "powerupmaxbombrangestatetest.h"
#include "powerupmaxbombrangestate.h"
#include "uniqueidcreator.h"
#include "playerstate.h"

using namespace Common;


void PowerUpMaxBombRangeStateTest::modifyPlayer_maxBombRange_2()
{
    UniqueIdCreator id;
    UniqueIdCreator idPlayer;
    PowerUpMaxBombRangeState increaseMaxBomb(id, Point());
    PlayerState player(idPlayer);
    unsigned int maxBombRange = player.getDestructionRangeOfNewBombs();


    increaseMaxBomb.modifyPlayer(player);

    CPPUNIT_ASSERT_EQUAL(maxBombRange+1,player.getDestructionRangeOfNewBombs());
}
