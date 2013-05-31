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

void DynamicObjectTest::applyLinearVelocity_5IntoXAndSimulationStepOf1_positionHasChanged5IntoX()
{
    PhysicSimulator simulator;
    DynamicObject object(simulator, Point(0, 0), 1, 1);

    object.applyLinearVelocity(5, 0);
    simulator.simulateStep(1);

    Point positionShouldBe(5, 0);
    Point positionReal(object.getPosition());
    CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void DynamicObjectTest::applyLinearVelocity_5IntoYAndSimulationStepOf01_positionHasChanged05IntoY()
{
    PhysicSimulator simulator;
    DynamicObject object(simulator, Point(0, 0), 1, 1);

    object.applyLinearVelocity(0, 5);
    simulator.simulateStep(0.1);

    Point positionShouldBe(0, 0.5);
    Point positionReal(object.getPosition());
    CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.0001));
}

void DynamicObjectTest::constructor_position5And4AndHeight2AndWidth2_centerPositionIs6And5()
{
    PhysicSimulator simulator;
    DynamicObject object(simulator, Point(5, 4), 2, 2);

    CPPUNIT_ASSERT(Point(6, 5).fuzzyEqual(object.getCenterPosition(), 0.0001));
}
