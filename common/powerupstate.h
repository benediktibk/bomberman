#ifndef COMMON_POWERUPSTATE_H
#define COMMON_POWERUPSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/playerstate.h"
#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
enum PowerUpType
    {
    PowerUpTypeNone,
    PowerUpTypeMaxBomb,
    PowerUpTypeMaxVelocity
    };

class PowerUpState :
        public ChangeableState,
        public DestroyableState
{
public:
    PowerUpState(UniqueIdCreator &creator, const Point &position);
    ~PowerUpState();

    const Point& getPosition() const;
    unsigned int getId() const;
    double getWidth() const;
    double getHeight() const;

    virtual void modifyPlayer(PlayerState &player) const;

protected:
    virtual void shouldBeDestroyed();

private:
    const Point m_position;
    const unsigned int m_powerUpId;
    UniqueIdCreator &m_creatorid;
    double m_width;
    double m_height;
};
}
#endif
