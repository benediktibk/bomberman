#include "playertest.h"
#include "player.h"
#include "physicsimulator.h"

using namespace Physic;
using namespace Common;

void PlayerTest::constructor_validDimensions_bodyCountOfSimulatorIs1()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 1, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, simulator.getBodyCount());
}

void PlayerTest::destructor_empty_bodyCountOfSimulatorIs0()
{
	PhysicSimulator simulator;
	Player *player = new Player(simulator, Point(), 1, 1);

	delete player;

	CPPUNIT_ASSERT_EQUAL((size_t)0, simulator.getBodyCount());
}

void PlayerTest::getPosition_positionSetTo2And3_2And3()
{
	PhysicSimulator simulator;
	Point positionShouldBe(2, 3);
	Player player(simulator, positionShouldBe, 1, 1);

	Point positionReal = player.getPosition();

	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void PlayerTest::getCenterPosition_positionSetTo2And3WithHeightAndWidth2_3And4()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 4);
	Player player(simulator, Point(2, 3), 2, 2);

	Point positionReal = player.getCenterPosition();

	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void PlayerTest::constructor_heightSetTo2_heightIs2()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 4, 2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getHeight(), 0.0001);
}

void PlayerTest::constructor_widthSetTo4_widthIs4()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 4, 2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getWidth(), 0.0001);
}

void PlayerTest::getPhysicalHeight_notMovingAndHeight4_4()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalWidth_notMovingAndWidth2_2()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 2, 4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::getPhysicalHeight_movingIntoXAndHeight4_2()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);
	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalHeight_movingIntoYAndHeight4_4()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);
	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getPhysicalHeight(), 0.0001);
}

void PlayerTest::getPhysicalWidth_movingIntoXAndWidth6_6()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);
	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::getPhysicalWidth_movingIntoYAndWith6_3()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);
	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, player.getPhysicalWidth(), 0.0001);
}

void PlayerTest::applyLinearVelocity_4And0_velocityXIs4()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);

	player.applyLinearVelocity(4, 0);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, player.getVelocityX(), 0.0001);
}

void PlayerTest::applyLinearVelocity_0And5_velocityYIs5()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);

	player.applyLinearVelocity(0, 5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, player.getVelocityY(), 0.0001);
}

void PlayerTest::applyLinearVelocity_4And0_bodyCountOfSimulatorIs1()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(), 6, 4);

	player.applyLinearVelocity(4, 0);

	CPPUNIT_ASSERT_EQUAL((size_t)1, simulator.getBodyCount());
}

void PlayerTest::getPosition_movingIntoX_correctPosition()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 2);
	Player player(simulator, positionShouldBe, 1, 1);

	player.applyLinearVelocity(1, 0);

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(player.getPosition(), 0.0001));
}

void PlayerTest::getPosition_movingIntoY_correctPosition()
{
	PhysicSimulator simulator;
	Point positionShouldBe(3, 2);
	Player player(simulator, positionShouldBe, 1, 1);

	player.applyLinearVelocity(0, 1);

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(player.getPosition(), 0.0001));
}

void PlayerTest::getCenterPosition_movingIntoX_correctPosition()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(3, 2), 1, 1);

	player.applyLinearVelocity(1, 0);

	Point positionShouldBe(3.5, 2.5);
	Point positionReal = player.getCenterPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PlayerTest::getCenterPosition_movingIntoY_correctPosition()
{
	PhysicSimulator simulator;
	Player player(simulator, Point(3, 2), 1, 1);

	player.applyLinearVelocity(0, 1);

	Point positionShouldBe(3.5, 2.5);
	Point positionReal = player.getCenterPosition();
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}