#include "powerupmaxbombrangestate.h"

using namespace Common;

PowerUpMaxBombRangeState::PowerUpMaxBombRangeState(UniqueIdCreator &creator, const Point &position):
	PowerUpState(creator, position, PowerUpTypeMaxBombRange),
    m_plusBombRange(1)
{ }

void PowerUpMaxBombRangeState::modifyPlayer(PlayerState &player) const
{
    player.increaseMaximumBombRange(m_plusBombRange);
}
