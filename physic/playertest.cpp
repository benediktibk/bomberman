#include "physic/playertest.h"
#include "physic/player.h"
#include "physic/physicsimulator.h"
#include "common/playerstate.h"
#include "common/uniqueidcreator.h"

using namespace Physic;
using namespace Common;
using namespace std;



void PlayerTest::constructor_validDimensions_bodyCountOfSimulatorIs1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	CPPUNIT_ASSERT_EQUAL((size_t)1, simulator.getBodyCount());
}

void PlayerTest::destructor_empty_bodyCountOfSimulatorIs0()
{
	PhysicSimulator simulator;
	Player *player = new Player(simulator, *m_playerOneState);

	delete player;

	CPPUNIT_ASSERT_EQUAL((size_t)0, simulator.getBodyCount());
}

void PlayerTest::getPosition_positionSetTo2And3_2And3()
{
	PhysicSimulator simulator;
	Point positionShouldBe(2, 3);
	m_playerOneState->setPosition(positionShouldBe);
	Player player(simulator, *m_playerOneState);

	Point positionReal = player.getPosition();

	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void PlayerTest::getCenterPosition_positionSetTo2And3WithHeightAndWidth2_3And4()
{
	PhysicSimulator simulator;
	m_playerOneState->setPosition(Point(3, 4));
	Player player(simulator, *m_playerOneState);

	Point positionReal = player.getCenterPosition();

	Point positionShouldBe(3.5, 4.5);
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void PlayerTest::constructor_dimensionSetTo1_dimensionIs1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getDimension(), 0.0001);
}

void PlayerTest::getPhysicalHeight_notMovingAndDimension1_1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalWidth_notMovingAndDimension1_1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::getPhysicalHeight_movingIntoXAndDimension1_05()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);
	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalHeight_movingIntoYAndDimension1_1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);
	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalWidth_movingIntoXAndDimension1_1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);
	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::getPhysicalWidth_movingIntoYAndDimension1_05()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);
	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::applyLinearVelocity_4And0_velocityXIs4()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	player.applyLinearVelocity(4, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getVelocityX(), 0.0001);
}

void PlayerTest::applyLinearVelocity_0And5_velocityYIs5()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	player.applyLinearVelocity(0, 5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, player.getVelocityY(), 0.0001);
}

void PlayerTest::getPosition_movingIntoX_correctPosition()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 2);
	m_playerOneState->setPosition(positionShouldBe);
	Player player(simulator, *m_playerOneState);

	player.applyLinearVelocity(1, 0);

	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getPosition_movingIntoY_correctPosition()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 2);
	m_playerOneState->setPosition(positionShouldBe);
	Player player(simulator, *m_playerOneState);

	player.applyLinearVelocity(0, 1);

	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getCenterPosition_movingIntoX_correctPosition()
{
	PhysicSimulator simulator;
	m_playerOneState->setPosition(Point(3, 2));
	Player player(simulator, *m_playerOneState);

	player.applyLinearVelocity(1, 0);

	Point positionShouldBe(3.5, 2.5);
	Point positionReal = player.getCenterPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getCenterPosition_movingIntoY_correctPosition()
{
	PhysicSimulator simulator;
	m_playerOneState->setPosition(Point(3, 2));
	Player player(simulator, *m_playerOneState);

	player.applyLinearVelocity(0, 1);

	Point positionShouldBe(3.5, 2.5);
	Point positionReal = player.getCenterPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getVelocityX_notMoving_0()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getVelocityX(), 0.00001);
}

void PlayerTest::getVelocityY_notMoving_0()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerOneState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getVelocityY(), 0.00001);
}

void PlayerTest::setUp()
{
	m_playerIDCreator = new UniqueIdCreator;
	m_playerOneState = new PlayerState(*m_playerIDCreator);
	m_playerTwoState = new PlayerState(*m_playerIDCreator);
}

void PlayerTest::tearDown()
{
	delete m_playerOneState;
	m_playerOneState = 0;
	delete m_playerTwoState;
	m_playerTwoState = 0;
	delete m_playerIDCreator;
	m_playerIDCreator = 0;

}

void PlayerTest::getCenterPosition_movingIntoYIntoOtherPlayer_correctPosition()
{
	PhysicSimulator simulator;
	m_playerOneState->setPosition(Point(1, 2));
	m_playerTwoState->setPosition(Point(3,2));
	Player playerOne(simulator, *m_playerOneState);
	Player playerTwo(simulator, *m_playerTwoState);

	playerOne.applyLinearVelocity(1, 0);
	simulator.simulateStep(0.5);
	playerOne.updateObstacle();

	playerTwo.applyLinearVelocity(-1, 0);
	playerTwo.updateObstacle();
	simulator.simulateStep(3);
	playerTwo.applyLinearVelocity(0, 0);
	Point positionPlayerOneShouldBe(2, 2);
	Point positionPlayerOneReal = playerOne.getPosition();
	Point positionPlayerTwoShouldBe(3, 2);
	Point positionPlayerTwoReal = playerTwo.getPosition();
	CPPUNIT_ASSERT(positionPlayerOneShouldBe.fuzzyEqual(positionPlayerOneReal, 0.05));
	CPPUNIT_ASSERT(positionPlayerTwoShouldBe.fuzzyEqual(positionPlayerTwoReal, 0.05));
}
