#ifndef COMMON_PLAYERSTATE_H
#define COMMON_PLAYERSTATE_H

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
    void countBomb();
    void reduceBombCount();
    unsigned int getBombCount();
    double getPlayerSpeed() const;
    double getPlayerWidth() const;
    double getPlayerHeight() const;


private:
	Point m_position;
	PlayerDirection m_PlayerDirection;
    unsigned int m_placedBombCount;
    double m_playerspeed;
    double m_width;
    double m_height;
};
}

#endif
