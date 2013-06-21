#ifndef GAMEENGINE_ROUTE_H
#define GAMEENGINE_ROUTE_H

#include "common/playerstate.h"

namespace GameEngine
{
	class Route
	{
	public:
		Route(unsigned int distance, Common::PlayerState::PlayerDirection direction);

		unsigned int getDistance() const;
		Common::PlayerState::PlayerDirection getDirection() const;

	private:
		unsigned int m_distance;
		Common::PlayerState::PlayerDirection m_direction;
	};
}

#endif
