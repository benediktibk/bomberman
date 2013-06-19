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

void PowerUpMaxBombRangeStateTest::modifyPlayer_baseClass_maxBombRangeIs2()
{
	UniqueIdCreator id;
	UniqueIdCreator idPlayer;
	PowerUpState *increaseMaxBomb = new PowerUpMaxBombRangeState(id, Point());
	PlayerState player(idPlayer);

	increaseMaxBomb->modifyPlayer(player);

	CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(2), player.getDestructionRangeOfNewBombs());
}
