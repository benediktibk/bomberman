#include "staticobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

StaticObject::StaticObject(PhysicSimulator &simulator, const Point &position, double width, double height) :
	m_simulator(simulator),
	m_body(0),
	m_bodyDef(new b2BodyDef),
	m_fixture(0),
	m_fixtureDef(new b2FixtureDef),
	m_shape(new b2PolygonShape),
	m_width(width),
	m_height(height)
{
	m_bodyDef->position.Set(position.getX() + width/2, position.getY() + height/2);
	m_body = simulator.createBody(*m_bodyDef);
	m_shape->SetAsBox(width/2, height/2);
	m_fixture = m_body->CreateFixture(m_shape, 0);
}

StaticObject::~StaticObject()
{
	m_simulator.destroyBody(m_body);
	delete m_fixtureDef;
	delete m_shape;
	delete m_bodyDef;
}

void StaticObject::setPosition(const Point &point)
{
	m_bodyDef->position.Set(point.getX() + m_width/2, point.getY() + m_height/2);
}


