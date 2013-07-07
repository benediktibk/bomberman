#ifndef COMMON_POWERUPSTATE_H
#define COMMON_POWERUPSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/playerstate.h"
#include "common/changedestroyablestate.h"

namespace Common
{
enum PowerUpType
    {
    PowerUpTypeNone,
    PowerUpTypeMaxBomb,
	PowerUpTypeMaxVelocity,
	PowerUpTypeMaxBombRange
    };

class PowerUpState :
        public ChangeDestroyableState
{
public:
	PowerUpState(UniqueIdCreator &creator, const Point &position, PowerUpType powerUpType = PowerUpTypeNone);
    ~PowerUpState();

    const Point& getPosition() const;
    unsigned int getId() const;
    double getWidth() const;
    double getHeight() const;
	PowerUpType getPowerUpType() const;

    virtual void modifyPlayer(PlayerState &player) const;

private:
    const Point m_position;
    const unsigned int m_powerUpId;
    UniqueIdCreator &m_creatorid;
    double m_width;
    double m_height;
	PowerUpType m_powerUpType;
};
}
#endif
