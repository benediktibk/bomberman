#include "physic/bombtest.h"
#include "physic/bomb.h"
#include "physic/player.h"
#include "physic/physicsimulator.h"
#include "common/point.h"
#include "common/bombstate.h"
#include "common/playerstate.h"

using namespace Physic;
using namespace Common;

void BombTest::doNotCollideWith_player_playerDoesntCollide()
{
	PhysicSimulator simulator;
	BombState bombState(m_bombIDCreator, 0, Point(3, 0), 1);
	Bomb bomb(simulator, bombState);
	PlayerState playerState(m_playerIDCreator);
	Player player(simulator, playerState);
	player.applyLinearVelocity(10, 0);

	bomb.doNotCollideWith(playerState);

	simulator.simulateStep(1);
	Point positionShouldBe(10, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void BombTest::collideWithEverything_doNotCollideWithCalled_playerCollides()
{
	PhysicSimulator simulator;
	BombState bombState(m_bombIDCreator, 0, Point(3, 0), 1);
	Bomb bomb(simulator, bombState);
	PlayerState playerState(m_playerIDCreator);
	Player player(simulator, playerState);
	player.applyLinearVelocity(10, 0);
	bomb.doNotCollideWith(playerState);

	bomb.collideWithEverything();

	simulator.simulateStep(1);
	Point positionShouldBe(2, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}
