#ifndef COMMON_WALLSTATE_H
#define COMMON_WALLSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"

namespace Common
{
class WallState
{
public:
    void setPosition(const Point &value);
    const Point& getPosition() const;

private:
    Point m_position;
};
}

#endif

