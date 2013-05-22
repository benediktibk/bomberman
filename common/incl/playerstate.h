#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

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

	void setPosition(double value);
	double getPosition() const;
    PlayerDirection getDirection() const;
    void setDirectionUp();
    void setDirectionDown();
    void setDirectionLeft();
    void setDirectionRight();

private:
	double m_position;
    PlayerDirection m_PlayerDirection;
};
}

#endif
