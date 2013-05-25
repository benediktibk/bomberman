#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "point.h"

namespace Common
{
class PlayerState
{
public:
    enum PlayerDirection
    {
        PlayerDirectionUp,
        PlayerDirectionDown,
        PlayerDirectionLeft,
        PlayerDirectionRight
    };

	PlayerState();

    void setPosition(Point value);
    Point getPosition() const;
    PlayerDirection getDirection() const;
    void setDirectionUp();
    void setDirectionDown();
    void setDirectionLeft();
    void setDirectionRight();

private:
    Point m_position;
    PlayerDirection m_PlayerDirection;
};
}

#endif
