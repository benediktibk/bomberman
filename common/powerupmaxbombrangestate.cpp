#include "powerupmaxbombrangestate.h"

using namespace Common;

PowerUpMaxBombRangeState::PowerUpMaxBombRangeState(UniqueIdCreator &creator, const Point &position):
    PowerUpState(creator, position),
    m_plusBombRange(1)
{ }

void PowerUpMaxBombState::modifyPlayer(PlayerState &player) const
{
    player.increaseMaxBombs(m_plusMaxBombs);
}
