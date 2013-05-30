#include "dynamicobjecttest.h"
#include "dynamicobject.h"
#include "physicsimulator.h"

using namespace Physic;
using namespace Common;

void DynamicObjectTest::constructor_position5And4AndHeight1AndWidth2_positionIs5And4()
{
	PhysicSimulator simulator;
	DynamicObject object(simulator, Point(5, 4), 1, 2);

	CPPUNIT_ASSERT(Point(5, 4).fuzzyEqual(object.getPosition(), 0.0001));
}

void DynamicObjectTest::constructor_validSimulator_simulatorHasBodyCount1()
{
	PhysicSimulator simulator;
	DynamicObject object(simulator, Point(), 1, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, simulator.getBodyCount());
}

void DynamicObjectTest::desturctor_empty_simulatorHasBodyCount0()
{
	PhysicSimulator simulator;
	DynamicObject *object = new DynamicObject(simulator, Point(), 1, 1);

	delete object;

	CPPUNIT_ASSERT_EQUAL((size_t)0, simulator.getBodyCount());
}
