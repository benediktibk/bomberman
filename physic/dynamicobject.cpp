#include "dynamicobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

DynamicObject::DynamicObject(PhysicSimulator &simulator, const Point &position, double width, double height) :
	m_simulator(simulator),
	m_bodyDefinition(new b2BodyDef),
	m_body(0),
	m_shape(new b2PolygonShape),
	m_fixtureDefinition(new b2FixtureDef),
	m_fixture(0),
	m_width(width),
	m_height(height)
{
	m_bodyDefinition->type = b2_dynamicBody;
	m_bodyDefinition->position.Set(position.getX() + width/2, position.getY() + height/2);
	m_body = simulator.createBody(*m_bodyDefinition);
	m_shape->SetAsBox(width/2, height/2);
	m_fixtureDefinition->shape = m_shape;
	m_fixture = m_body->CreateFixture(m_fixtureDefinition);
}

DynamicObject::~DynamicObject()
{
	m_simulator.destroyBody(m_body);
	delete m_fixtureDefinition;
	delete m_shape;
	delete m_bodyDefinition;
}

Point DynamicObject::getPosition() const
{
	b2Vec2 position = m_body->GetPosition();
	Point pointposition(position.x - m_width/2, position.y - m_height/2);
	return pointposition;
}

void DynamicObject::applyLinearVelocity(double velocityx, double velocityy)
{
	b2Vec2 vel;
	vel.x = velocityx;
	vel.y = velocityy;
	m_body->SetLinearVelocity(vel);
}

Point DynamicObject::getCenterPosition() const
{
    b2Vec2 position = m_body->GetPosition();
    Point pointposition(position.x, position.y);
    return pointposition;
}
