#include "staticobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

StaticObject::StaticObject(PhysicSimulator &simulator) :
    m_body(0),
    m_bodyDef(new b2BodyDef),
    m_fixture(0),
    m_fixtureDef(new b2FixtureDef),
    m_shape(new b2PolygonShape)
{
    m_bodyDefinition->position.Set(0, 0);
    m_body = simulator.createBody(*m_bodyDef);
    m_shape->SetAsBox(100, 100);
    m_fixture = m_body->CreateFixture(m_shape, 0);
}

StaticObject::~StaticObject()
{
    delete m_fixtureDef;
    delete m_shape;
    delete m_bodyDef;
}

Point StaticObject::getPosition() const
{
    b2Vec2 position = m_body->GetPosition();
    Point pointposition(position.x,position.y);
    return pointposition;
}
