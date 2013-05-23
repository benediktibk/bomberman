#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

namespace Common
{
class EnemyState
{
public:
	EnemyState();

	void setPosition(double value);
	double getPosition() const;

private:
	double m_position;
};
}

#endif
