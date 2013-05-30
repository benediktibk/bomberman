#include "physicsimulator.h"
#include "Box2D/Box2D.h"
#include <assert.h>

using namespace Physic;

PhysicSimulator::PhysicSimulator() :
	m_gravity(new b2Vec2(0, 0)),
	m_world(new b2World(*m_gravity)),
	m_velocityIterations(6),
	m_positionIterations(2),
	m_bodyCount(0),
	m_maximumTimeStep(1.0/8)
{
	m_world->SetAllowSleeping(true);
}

PhysicSimulator::~PhysicSimulator()
{
	assert(m_bodyCount == 0);
	delete m_world;
	delete m_gravity;
}

b2Body* PhysicSimulator::createBody(const b2BodyDef &definition)
{
	++m_bodyCount;
	return m_world->CreateBody(&definition);
}

void PhysicSimulator::destroyBody(b2Body *body)
{
	--m_bodyCount;
	m_world->DestroyBody(body);
}

void PhysicSimulator::simulateStep(double time)
{
	double factor = time/m_maximumTimeStep;

	if (factor < 1)
		m_world->Step(time, m_velocityIterations, m_positionIterations);
	else
	{
		size_t fullTimeParts = static_cast<size_t>(factor);
		double restTime = time - fullTimeParts*m_maximumTimeStep;

		for (size_t i = 0; i < fullTimeParts; ++i)
			m_world->Step(m_maximumTimeStep, m_velocityIterations, m_positionIterations);

		m_world->Step(restTime, m_velocityIterations, m_positionIterations);
	}
}

size_t PhysicSimulator::getBodyCount() const
{
	return m_bodyCount;
}
