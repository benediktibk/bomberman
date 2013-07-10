#ifndef COMMON_BOMBSTATE_H
#define COMMON_BOMBSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/changeableanddestroyablestate.h"

namespace Common
{
	class BombState :
			public ChangeableAndDestroyableState
	{
	public:
		BombState(UniqueIdCreator &creator, unsigned int playerID, const Point &position, unsigned int destructionRange);
		~BombState();

		const Point& getPosition() const;
		void setLifeTime(double time);
		double getLifeTime() const;
		unsigned int getDestructionRange() const;
		unsigned int getID() const;
		double getDimension() const;
		unsigned int getPlayerID() const;

	public:
		static double initialLifeTime();

	private:
		// forbid copies
		BombState(const BombState &bomb);
		void operator=(const BombState &bomb);

	private:
		const unsigned int m_playerID;
		const Point m_position;
		double m_lifeTime;
		const double m_dimension;
		const unsigned int m_destructionRange;
		const unsigned int m_bombId;
		UniqueIdCreator &m_creatorId;
	};
}

#endif
