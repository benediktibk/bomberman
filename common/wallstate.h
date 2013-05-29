#ifndef COMMON_WALLSTATE_H
#define COMMON_WALLSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"

namespace Common
{
class WallState
{
public:
    WallState(UniqueIdCreator &creator);
    ~WallState();
    void setPosition(const Point &value);
    const Point& getPosition() const;
    unsigned int getWallId() const;
private:
    Point m_position;
    unsigned int m_wallid;
    UniqueIdCreator &m_creatorid;
};
}

#endif

