#include "powerupmaxvelocitystate.h"

using namespace Common;

PowerUpMaxVelocityState::PowerUpMaxVelocityState(UniqueIdCreator &creator, const Point &position):
	PowerUpState(creator, position, PowerUpTypeMaxVelocity)
{ }

void PowerUpMaxVelocityState::modifyPlayer(PlayerState &player) const
{
    player.increaseSpeed();
}

