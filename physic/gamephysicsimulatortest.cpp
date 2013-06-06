#include "physic/gamephysicsimulatortest.h"
#include "physic/gamephysicsimulator.h"
#include "common/leveldefinition.h"
#include "common/gamestate.h"

using namespace Physic;
using namespace Common;

void GamePhysicSimulatorTest::simulateStep_movePlayerTowardsWall_playerCollidesWithWall()
{
	LevelDefinition level(5, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 0);
	GameState gameState(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &player = gameState.getPlayerState();
	GamePhysicSimulator simulator(level, player);
	player.setDirectionRight();
	player.setMoving();
	simulator.updateItems(gameState);

	simulator.simulateStep(player, 100);

	Point positionShouldBe(2, 0);
	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GamePhysicSimulatorTest::simulateStep_movePlayerTowardsBomb_playerCollidesWithBomb()
{
	LevelDefinition level(5, 10);
	GameState gameState(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &player = gameState.getPlayerState();
	GamePhysicSimulator simulator(level, player);
	player.setDirectionRight();
	player.setMoving();
	BombState *bomb = new BombState(m_bombIDCreator);
	bomb->setPosition(Point(3, 0));
	gameState.addBomb(bomb);
	simulator.updateItems(gameState);

	simulator.simulateStep(player, 100);

	Point positionShouldBe(2, 0);
	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}
