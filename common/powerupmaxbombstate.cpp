#include "powerupmaxbombstate.h"

using namespace Common;

PowerUpMaxBombState::PowerUpMaxBombState(UniqueIdCreator &creator, const Point &position):
    PowerUpState(creator, position),
    m_plusMaxBombs(1)
{ }

void PowerUpMaxBombState::modifyPlayer(PlayerState &player)
{
    unsigned int maxBombs;
    maxBombs = player.getMaxBombs();
    maxBombs += m_plusMaxBombs;

    player.setMaxBombs(maxBombs);
}
