#ifndef COMMON_POWERUPMAXBOMBRANGESTATE_H
#define COMMON_POWERUPMAXBOMBRANGESTATE_H

#include "powerupstate.h"

namespace Common
{
class PowerUpMaxBombRangeState :
        public PowerUpState
{
public:
    PowerUpMaxBombRangeState(UniqueIdCreator &creator, const Point &position);

    void modifyPlayer(PlayerState &player) const;

private:
    unsigned int m_plusBombRange;
};
}
#endif
