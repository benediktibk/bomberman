#include "physic/physicalobjecttest.h"
#include "physic/physicalobject.h"
#include "physic/physicsimulator.h"
#include "common/point.h"

using namespace Physic;
using namespace Common;

void PhysicalObjectTest::setUp()
{
	m_simulator = new PhysicSimulator;
}

void PhysicalObjectTest::tearDown()
{
	delete m_simulator;
	m_simulator = 0;
}

void PhysicalObjectTest::setCollisionGroup_5_collisionGroupIs5()
{
	PhysicalObject object(*m_simulator, Point(), 1, 1, PhysicalObject::BodyTypeStatic);

	object.setCollisionGroup(5);

	CPPUNIT_ASSERT_EQUAL((int16_t)5, object.getCollisionGroup());
}
