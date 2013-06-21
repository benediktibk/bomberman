#include "gameengine/route.h"

using namespace GameEngine;

Route::Route(unsigned int distance, Common::PlayerState::PlayerDirection direction) :
	m_distance(distance),
	m_direction(direction)
{ }

unsigned int Route::getDistance() const
{
	return m_distance;
}

Common::PlayerState::PlayerDirection Route::getDirection() const
{
	return m_direction;
}
