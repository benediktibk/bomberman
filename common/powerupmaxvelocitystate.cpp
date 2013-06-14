#include "powerupmaxvelocitystate.h"

using namespace Common;

PowerUpMaxVelocityState::PowerUpMaxVelocityState(UniqueIdCreator &creator, const Point &position):
    PowerUpState(creator, position)
{ }

void PowerUpMaxVelocityState::modifyPlayer(PlayerState &player) const
{
    player.increaseMaximumSpeed();
}

