#include "powerupmaxbombstate.h"

using namespace Common;

PowerUpMaxBombState::PowerUpMaxBombState(UniqueIdCreator &creator, const Point &position):
	PowerUpState(creator, position, PowerUpTypeMaxBomb),
    m_plusMaxBombs(1)
{ }

void PowerUpMaxBombState::modifyPlayer(PlayerState &player) const
{
    player.increaseMaxBombs(m_plusMaxBombs);
}
