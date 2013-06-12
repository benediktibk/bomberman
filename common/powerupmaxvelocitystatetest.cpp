#include "powerupmaxvelocitystatetest.h"
#include "powerupmaxvelocitystate.h"
#include "uniqueidcreator.h"
#include "playerstate.h"

using namespace Common;


void PowerUpMaxVelocityStateTest::modifyPlayer_maxSpeed_7()
{
    UniqueIdCreator id;
    UniqueIdCreator idPlayer;
    PowerUpMaxVelocityState increaseMaxVel(id, Point());
    PlayerState player(idPlayer);
    double speed = player.getMaximumSpeed();


    increaseMaxVel.modifyPlayer(player);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(speed+2,player.getMaximumSpeed(),0.001);
}
