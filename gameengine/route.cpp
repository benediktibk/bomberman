#include "gameengine/route.h"

using namespace GameEngine;

Route::Route(unsigned int distance, Common::PlayerState::PlayerDirection direction, const Common::GridPoint target) :
	m_distance(distance),
	m_direction(direction),
	m_targetPosition(target)
{ }

unsigned int Route::getDistance() const
{
	return m_distance;
}

Common::PlayerState::PlayerDirection Route::getDirection() const
{
	return m_direction;
}

const Common::GridPoint Route::getTargetPosition() const
{
	return m_targetPosition;
}
