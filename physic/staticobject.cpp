#include "staticobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

StaticObject::StaticObject(PhysicSimulator &simulator, const Point &position, double width, double height) :
	m_body(0),
	m_bodyDef(new b2BodyDef),
	m_fixture(0),
	m_fixtureDef(new b2FixtureDef),
	m_shape(new b2PolygonShape)
{
	m_bodyDef->position.Set(position.getX(),position.getY());
	m_body = simulator.createBody(*m_bodyDef);
	m_shape->SetAsBox(width, height);
	m_fixture = m_body->CreateFixture(m_shape, 0);
}

StaticObject::~StaticObject()
{
	delete m_fixtureDef;
	delete m_shape;
	delete m_bodyDef;
}

void StaticObject::SetPosition(const Point &point)
{
	m_bodyDef->position.Set(point.getX(), point.getY());
}

//void StaticObject::DestroyBody()
//{

//    m_body->DestroyFixture();
//}


