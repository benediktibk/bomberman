#ifndef COMMON_BOMBSTATE_H
#define COMMON_BOMBSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
class BombState :
		public ChangeableState,
		public DestroyableState
{
public:
	BombState(UniqueIdCreator &creator);
	~BombState();
	void setPosition(const Point &value);
	const Point& getPosition() const;
	void setLifeTime(double time);
	double getLifeTime() const;
	void setDestructionRange(int range);
	unsigned int getDestructionRange() const;
	unsigned int getBombId() const;
	double getWidth() const;
	double getHeight() const;

private:
	// forbid copies
	BombState(const BombState &bomb);
	void operator=(const BombState &bomb);

protected:
	virtual void shouldBeDestroyed();

private:
	Point m_position;
	double m_lifeTime;
	double m_width;
	double m_height;
	unsigned int m_destructionRange;
	unsigned int m_bombId;
	UniqueIdCreator &m_creatorId;
};
}

#endif
