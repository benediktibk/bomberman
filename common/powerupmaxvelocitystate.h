#ifndef COMMON_POWERUPMAXVELOCITYSTATE_H
#define COMMON_POWERUPMAXVELOCITYSTATE_H

#include "powerupstate.h"

namespace Common
{
class PowerUpMaxVelocityState :
        public PowerUpState
{
public:
    PowerUpMaxVelocityState(UniqueIdCreator &creator, const Point &position);

    void modifyPlayer(PlayerState &player) const;

private:

};
}
#endif
