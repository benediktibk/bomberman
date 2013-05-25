#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;

PhysicSimulator::PhysicSimulator() :
    m_gravity(new b2Vec2(0, 0)),
	m_world(new b2World(*m_gravity)),
	m_velocityIterations(6),
	m_positionIterations(2)
{
	m_world->SetAllowSleeping(true);
}

PhysicSimulator::~PhysicSimulator()
{
	delete m_world;
	delete m_gravity;
}

b2Body* PhysicSimulator::createBody(const b2BodyDef &definition)
{
	return m_world->CreateBody(&definition);
}

void PhysicSimulator::simulateStep(double time)
{
	m_world->Step(time, m_velocityIterations, m_positionIterations);
}
