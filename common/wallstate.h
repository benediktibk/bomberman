#ifndef COMMON_WALLSTATE_H
#define COMMON_WALLSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"

namespace Common
{
class WallState
{
public:
    enum WallType
    {
        WallTypeSolid,
        WallTypeLoose
    };

    WallState(UniqueIdCreator &creator, WallType wallType);
    ~WallState();
    void setPosition(const Point &value);
    const Point& getPosition() const;
    WallType getWallType() const;

private:
    Point m_position;
    unsigned int m_wallid;
    UniqueIdCreator &m_creatorid;
    const WallType m_wallType;
};
}

#endif

