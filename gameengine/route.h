#ifndef GAMEENGINE_ROUTE_H
#define GAMEENGINE_ROUTE_H

#include "common/playerstate.h"
#include "common/gridpoint.h"

namespace GameEngine
{
	class Route
	{
	public:
		Route(unsigned int distance, Common::PlayerState::PlayerDirection direction, const Common::GridPoint target = Common::GridPoint(0,0));

		unsigned int getDistance() const;
		Common::PlayerState::PlayerDirection getDirection() const;
		const Common::GridPoint getTargetPosition() const;

	private:
		unsigned int m_distance;
		Common::PlayerState::PlayerDirection m_direction;
		const Common::GridPoint m_targetPosition;
	};
}

#endif
