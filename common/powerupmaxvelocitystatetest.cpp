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
	double speed = player.getSpeed();

	increaseMaxVel.modifyPlayer(player);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(speed + player.getSpeedIncrement(), player.getSpeed(), 0.001);
}

void PowerUpMaxVelocityStateTest::modifyPlayer_baseClass_maxSpeed_7()
{
	UniqueIdCreator id;
	UniqueIdCreator idPlayer;
	PowerUpState *increaseMaxVel = new PowerUpMaxVelocityState(id, Point());
	PlayerState player(idPlayer);
	double speed = player.getSpeed();

	increaseMaxVel->modifyPlayer(player);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(speed + player.getSpeedIncrement(), player.getSpeed(), 0.001);
}

void PowerUpMaxVelocityStateTest::getPowerUpType_isMaxVelocity()
{
	UniqueIdCreator id;
	PowerUpMaxVelocityState increaseMaxVel(id, Point());

	CPPUNIT_ASSERT_EQUAL(PowerUpTypeMaxVelocity, increaseMaxVel.getPowerUpType());
}
