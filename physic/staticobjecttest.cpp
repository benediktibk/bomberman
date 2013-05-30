#include "staticobjecttest.h"
#include "staticobject.h"
#include "physicsimulator.h"

using namespace Physic;
using namespace Common;

void StaticObjectTest::constructor_position5And4AndHeight1AndWidth2_positionIs5And4()
{
	PhysicSimulator simulator;
	StaticObject object(simulator, Point(5, 4), 1, 2);

	CPPUNIT_ASSERT(Point(5, 4).fuzzyEqual(object.getPosition(), 0.0001));
}

void StaticObjectTest::constructor_validSimulator_simulatorHasBodyCount1()
{
	PhysicSimulator simulator;
	StaticObject object(simulator, Point(), 1, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, simulator.getBodyCount());
}

void StaticObjectTest::desturctor_empty_simulatorHasBodyCount0()
{
	PhysicSimulator simulator;
	StaticObject *object = new StaticObject(simulator, Point(), 1, 1);

	delete object;

	CPPUNIT_ASSERT_EQUAL((size_t)0, simulator.getBodyCount());
}
