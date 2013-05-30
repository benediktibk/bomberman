#include "physicsimulatortest.h"
#include "physicsimulator.h"
#include "dynamicobject.h"

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