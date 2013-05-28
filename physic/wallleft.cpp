#include "wallleft.h"

#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

WallLeft::WallLeft(PhysicSimulator &simulator) :
    m_body(0),
    m_bodyDef(new b2BodyDef),
    m_fixture(0),
    m_fixtureDef(new b2FixtureDef),
    m_shape(new b2PolygonShape)
{
    m_bodyDef->position.Set(-8.5,0);
    m_body = simulator.createBody(*m_bodyDef);
    m_shape->SetAsBox(1 , 13 );
    m_fixture = m_body->CreateFixture(m_shape, 0);
}

WallLeft::~WallLeft()
{
    delete m_fixtureDef;
    delete m_shape;
    delete m_bodyDef;
}
