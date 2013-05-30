#ifndef COMMON_POWERUP_H
#define COMMON_POWERUP_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/playerstate.h"
#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
class PowerUp :
        public ChangeableState,
        public DestroyableState
{
public:
    PowerUp(UniqueIdCreator &creator, const Point &position);
    ~PowerUp();

    const Point& getPosition() const;
    unsigned int getId() const;
    double getWidth() const;
    double getHeight() const;

    virtual void modifyPlayer(PlayerState &player);

private:
    const Point m_position;
    const unsigned int m_powerUpId;
    UniqueIdCreator &m_creatorid;
    double m_width;
    double m_height;
};
}
#endif // POWERUP_H
