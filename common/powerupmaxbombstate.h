#ifndef COMMON_POWERUPMAXBOMBSTATE_H
#define COMMON_POWERUPMAXBOMBSTATE_H

#include "powerupstate.h"

namespace Common
{
class PowerUpMaxBombState :
        public PowerUpState
{
public:
    PowerUpMaxBombState(UniqueIdCreator &creator, const Point &position);

    void modifyPlayer(PlayerState &player);

private:
    unsigned int m_plusMaxBombs;
};
}
#endif
