#include "physicsimulatortest.h"
#include "physicsimulator.h"
#include "dynamicobject.h"
#include "staticobject.h"

using namespace Physic;
using namespace Common;

void PhysicSimulatorTest::simulateStep_timeBelowMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect()
{
	PhysicSimulator simulator;
	DynamicObject object(simulator, Point(), 1, 1);
	object.applyLinearVelocity(3, 2);

	simulator.simulateStep(0.1);

	Point positionShouldBe(0.3, 0.2);
	Point positionReal(object.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void Physic::PhysicSimulatorTest::simulateStep_timeAboveMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect()
{
	PhysicSimulator simulator;
	DynamicObject object(simulator, Point(), 1, 1);
	object.applyLinearVelocity(3, 2);

	simulator.simulateStep(3.3);

	Point positionShouldBe(9.9, 6.6);
	Point positionReal(object.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void PhysicSimulatorTest::simulateStep_collisionOfDynamicWithStaticObject_dynamicObjectPositionIsCorrect()
{
	PhysicSimulator simulator;
	StaticObject *staticObject = new StaticObject(simulator, Point(3, 0), 1, 1);
	DynamicObject *dynamicObject = new DynamicObject(simulator, Point(0, 0), 1, 1);
	dynamicObject->applyLinearVelocity(10, 0);

	simulator.simulateStep(1);

	Point positionShouldBe(2, 0);
	Point positionReal(dynamicObject->getPosition());
	delete staticObject;
	delete dynamicObject;
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void PhysicSimulatorTest::simulateStep_collisionOfDynamicWithStaticObject_staticObjectPositionIsNotChanged()
{
	PhysicSimulator simulator;
	StaticObject *staticObject = new StaticObject(simulator, Point(3, 0), 1, 1);
	DynamicObject *dynamicObject = new DynamicObject(simulator, Point(0, 0), 1, 1);
	dynamicObject->applyLinearVelocity(10, 0);

	simulator.simulateStep(1);

	Point positionShouldBe(3, 0);
	Point positionReal(staticObject->getPosition());
	delete staticObject;
	delete dynamicObject;
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void PhysicSimulatorTest::simulateStep_collisionOfDynamicWithDynamicObject_firstDynamicObjectPositionIsCorrect()
{
	PhysicSimulator simulator;
	DynamicObject *objectOne = new DynamicObject(simulator, Point(3, 0), 1, 1);
	DynamicObject *objectTwo = new DynamicObject(simulator, Point(0, 0), 1, 1);
	objectTwo->applyLinearVelocity(10, 0);

	simulator.simulateStep(1);

	Point positionShouldBe(7, 0);
	Point positionReal(objectOne->getPosition());
	delete objectOne;
	delete objectTwo;
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void PhysicSimulatorTest::simulateStep_collisionOfDynamicWithDynamicObject_secondDynamicObjectPositionIsCorrect()
{
	PhysicSimulator simulator;
	DynamicObject *objectOne = new DynamicObject(simulator, Point(3, 0), 1, 1);
	DynamicObject *objectTwo = new DynamicObject(simulator, Point(0, 0), 1, 1);
	objectTwo->applyLinearVelocity(10, 0);

	simulator.simulateStep(1);

	Point positionShouldBe(6, 0);
	Point positionReal(objectTwo->getPosition());
	delete objectOne;
	delete objectTwo;
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}
