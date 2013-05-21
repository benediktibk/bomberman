#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

namespace Common
{
class PlayerState
{
public:
	PlayerState();

	void setPosition(double value);
	double getPosition() const;

private:
	double m_position;
};
}

#endif
