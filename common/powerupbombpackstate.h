#ifndef COMMON_POWERUPBOMBPACKSTATE_H
#define COMMON_POWERUPBOMBPACKSTATE_H

#include "powerupstate.h"

namespace Common
{
class PowerUpBombPackState :
        public PowerUpState
{
public:
    PowerUpBombPackState(UniqueIdCreator &creator, const Point &position);

    void modifyPlayer(PlayerState &player);

private:
    unsigned int m_BombsInPackage;
};
}

#endif
