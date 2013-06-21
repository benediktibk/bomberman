#include "gameengine/routetest.h"
#include "gameengine/route.h"

using namespace GameEngine;
using namespace Common;

void RouteTest::constructor_distance5_distanceIs5()
{
	Route route(5, PlayerState::PlayerDirectionUp);

	CPPUNIT_ASSERT_EQUAL((unsigned int)5, route.getDistance());
}

void RouteTest::constructor_directionIsUp_directionIsUp()
{
	Route route(5, PlayerState::PlayerDirectionUp);

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, route.getDirection());
}
