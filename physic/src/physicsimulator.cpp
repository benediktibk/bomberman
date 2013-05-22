#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;

PhysicSimulator::PhysicSimulator() :
	m_gravity(new b2Vec2(0, -9.81)),
	m_world(new b2World(*m_gravity))
{
	m_world->SetAllowSleeping(true);
}

PhysicSimulator::~PhysicSimulator()
{
	delete m_world;
	delete m_gravity;
}
