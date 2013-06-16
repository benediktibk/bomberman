#include "physic/gamephysicsimulatortest.h"
#include "physic/gamephysicsimulator.h"
#include "common/leveldefinition.h"
#include "common/gamestate.h"

using namespace Physic;
using namespace Common;

void GamePhysicSimulatorTest::simulateStep_movePlayerTowardsWall_playerCollidesWithWall()
{
	LevelDefinition level(5, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 0);
	GameState gameState(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &player = gameState.getFirstPlayerState();
	GamePhysicSimulator simulator(level);
	player.setDirectionRight();
	player.setMoving();
	simulator.updateItems(gameState);

	simulator.simulateStep(gameState, 100);

	Point positionShouldBe(2, 0);
	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GamePhysicSimulatorTest::simulateStep_movePlayerTowardsBomb_playerCollidesWithBomb()
{
	LevelDefinition level(5, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	GameState gameState(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &player = gameState.getFirstPlayerState();
	GamePhysicSimulator simulator(level);
	player.setDirectionRight();
	player.setMoving();
	BombState *bomb = new BombState(m_bombIDCreator, player.getId());
	bomb->setPosition(Point(3, 0));
	gameState.addBomb(bomb);
	simulator.updateItems(gameState);

	simulator.simulateStep(gameState, 100);

	Point positionShouldBe(2, 0);
	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GamePhysicSimulatorTest::simulateStep_twoPlayersAndOneMovesTowardsTheOther_playersCollide()
{
	LevelDefinition level(5, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 0);
	GameState gameState(level, 2, m_playerIDCreator, m_wallIDCreator);
	PlayerState &playerOne = gameState.getFirstPlayerState();
	PlayerState &playerTwo = gameState.getSecondPlayerState();
	GamePhysicSimulator simulator(level);
	playerOne.setDirectionRight();
	playerOne.setMoving();
	playerOne.setPosition(Point(0, 0));
	playerTwo.setPosition(Point(3, 0));
	double timeForOneField = 1/playerOne.getMaximumSpeed();

	simulator.simulateStep(gameState, 4*timeForOneField);

	Point positionShouldBe(2, 0);
	Point positionReal = playerOne.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GamePhysicSimulatorTest::simulateStep_twoPlayersAndOneMovesTowardsTheOther_playerTwoDoesntMove()
{
	LevelDefinition level(5, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 0);
	GameState gameState(level, 2, m_playerIDCreator, m_wallIDCreator);
	PlayerState &playerOne = gameState.getFirstPlayerState();
	PlayerState &playerTwo = gameState.getSecondPlayerState();
	GamePhysicSimulator simulator(level);
	playerOne.setDirectionRight();
	playerOne.setMoving();
	playerOne.setPosition(Point(0, 0));
	playerTwo.setPosition(Point(3, 0));
	double timeForOneField = 1/playerOne.getMaximumSpeed();

	simulator.simulateStep(gameState, 4*timeForOneField);

	Point positionShouldBe(3, 0);
	Point positionReal = playerTwo.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}
