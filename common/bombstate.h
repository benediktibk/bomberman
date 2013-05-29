#ifndef COMMON_BOMBSTATE_H
#define COMMON_BOMBSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/changeablestate.h"

namespace Common
{
class BombState :
		public ChangeableState
{
public:
	BombState(UniqueIdCreator &creator);
	~BombState();
	void setPosition(const Point &value);
	const Point& getPosition() const;
	void setLifeTime(double time);
	double getLifeTime() const;
	void setDestructionRange(int range);
	int getDestructionRange() const;
    unsigned int getBombId() const;
private:
	Point m_position;
	double m_lifeTime;
	int m_destructionRange;
	unsigned int m_bombid;
	UniqueIdCreator &m_creatorid;
};
}

#endif
