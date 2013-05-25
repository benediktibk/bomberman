#include "dynamicobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

DynamicObject::DynamicObject(PhysicSimulator &simulator) :
	m_bodyDefinition(new b2BodyDef),
	m_body(0),
	m_shape(new b2PolygonShape),
	m_fixtureDefinition(new b2FixtureDef),
	m_fixture(0)
{
	m_bodyDefinition->type =  b2_dynamicBody;
	m_bodyDefinition->position.Set(0, 0);
	m_body = simulator.createBody(*m_bodyDefinition);
	m_shape->SetAsBox(1, 1);
	m_fixtureDefinition->shape = m_shape;
	m_fixtureDefinition->density = 15;
	m_fixture = m_body->CreateFixture(m_fixtureDefinition);
}

DynamicObject::~DynamicObject()
{
	delete m_fixtureDefinition;
	delete m_shape;
	delete m_bodyDefinition;
}

Point DynamicObject::getPosition() const
{
    b2Vec2 position = m_body->GetPosition();
    Point pointposition(position.x,position.y);
    return pointposition;
}

void DynamicObject::applyLinearVelocity(double velocityx, double velocityy)
{
    b2Vec2 vel;
    vel.x=velocityx;
    vel.y=velocityy;
    m_body->SetLinearVelocity(vel);
}
