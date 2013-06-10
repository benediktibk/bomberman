#include "physic/playertest.h"
#include "physic/player.h"
#include "physic/physicsimulator.h"
#include "common/playerstate.h"
#include "common/uniqueidcreator.h"

using namespace Physic;
using namespace Common;

void PlayerTest::constructor_validDimensions_bodyCountOfSimulatorIs1()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_EQUAL((size_t)1, simulator.getBodyCount());
}

void PlayerTest::destructor_empty_bodyCountOfSimulatorIs0()
{
	PhysicSimulator simulator;
	Player *player = new Player(simulator, *m_playerState);

	delete player;

	CPPUNIT_ASSERT_EQUAL((size_t)0, simulator.getBodyCount());
}

void PlayerTest::getPosition_positionSetTo2And3_2And3()
{
	PhysicSimulator simulator;
	Point positionShouldBe(2, 3);
	m_playerState->setPosition(positionShouldBe);
	Player player(simulator, *m_playerState);

	Point positionReal = player.getPosition();

	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void PlayerTest::getCenterPosition_positionSetTo2And3WithHeightAndWidth2_3And4()
{
	PhysicSimulator simulator;
	m_playerState->setPosition(Point(3, 4));
	Player player(simulator, *m_playerState);

	Point positionReal = player.getCenterPosition();

	Point positionShouldBe(3.5, 4.5);
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void PlayerTest::constructor_heightSetTo2_heightIs2()
{
	PhysicSimulator simulator;
	m_playerState->setHeight(2);
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getHeight(), 0.0001);
}

void PlayerTest::constructor_widthSetTo4_widthIs4()
{
	PhysicSimulator simulator;
	m_playerState->setWidth(4);
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getWidth(), 0.0001);
}

void PlayerTest::getPhysicalHeight_notMovingAndHeight4_4()
{
	PhysicSimulator simulator;
	m_playerState->setHeight(4);
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalWidth_notMovingAndWidth2_2()
{
	PhysicSimulator simulator;
	m_playerState->setWidth(2);
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::getPhysicalHeight_movingIntoXAndHeight4_2()
{
	PhysicSimulator simulator;
	m_playerState->setHeight(4);
	Player player(simulator, *m_playerState);
	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalHeight_movingIntoYAndHeight4_4()
{
	PhysicSimulator simulator;
	m_playerState->setHeight(4);
	Player player(simulator, *m_playerState);
	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalWidth_movingIntoXAndWidth6_6()
{
	PhysicSimulator simulator;
	m_playerState->setWidth(6);
	Player player(simulator, *m_playerState);
	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::getPhysicalWidth_movingIntoYAndWith6_3()
{
	PhysicSimulator simulator;
	m_playerState->setWidth(6);
	Player player(simulator, *m_playerState);
	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::applyLinearVelocity_4And0_velocityXIs4()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerState);

	player.applyLinearVelocity(4, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getVelocityX(), 0.0001);
}

void PlayerTest::applyLinearVelocity_0And5_velocityYIs5()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerState);

	player.applyLinearVelocity(0, 5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, player.getVelocityY(), 0.0001);
}


void PlayerTest::getPosition_movingIntoX_correctPosition()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 2);
	m_playerState->setPosition(positionShouldBe);
	Player player(simulator, *m_playerState);

	player.applyLinearVelocity(1, 0);

	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getPosition_movingIntoY_correctPosition()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 2);
	m_playerState->setPosition(positionShouldBe);
	Player player(simulator, *m_playerState);

	player.applyLinearVelocity(0, 1);

	Point positionReal = player.getPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getCenterPosition_movingIntoX_correctPosition()
{
	PhysicSimulator simulator;
	m_playerState->setPosition(Point(3, 2));
	Player player(simulator, *m_playerState);

	player.applyLinearVelocity(1, 0);

	Point positionShouldBe(3.5, 2.5);
	Point positionReal = player.getCenterPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getCenterPosition_movingIntoY_correctPosition()
{
	PhysicSimulator simulator;
	m_playerState->setPosition(Point(3, 2));
	Player player(simulator, *m_playerState);

	player.applyLinearVelocity(0, 1);

	Point positionShouldBe(3.5, 2.5);
	Point positionReal = player.getCenterPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getVelocityX_notMoving_0()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getVelocityX(), 0.00001);
}

void PlayerTest::getVelocityY_notMoving_0()
{
	PhysicSimulator simulator;
	Player player(simulator, *m_playerState);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getVelocityY(), 0.00001);
}

void PlayerTest::setUp()
{
	m_playerIDCreator = new UniqueIdCreator;
	m_playerState = new PlayerState(*m_playerIDCreator);
}

void PlayerTest::tearDown()
{
	delete m_playerState;
	m_playerState = 0;
	delete m_playerIDCreator;
	m_playerIDCreator = 0;
}
