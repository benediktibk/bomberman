#include "physicalobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"
#include <assert.h>

using namespace Physic;
using namespace Common;

b2BodyType convertToBox2DBodyType(PhysicalObject::BodyType bodyType)
{
	switch (bodyType)
	{
	case PhysicalObject::BodyTypeDynamic:
		return b2_dynamicBody;
	case PhysicalObject::BodyTypeStatic:
		return b2_staticBody;
	}

	assert(false);
	return b2_dynamicBody;
}

PhysicalObject::PhysicalObject(PhysicSimulator &simulator, const Point &position, double width, double height, BodyType bodyType) :
	m_simulator(simulator),
	m_bodyDefinition(new b2BodyDef),
	m_body(0),
	m_shape(new b2PolygonShape),
	m_fixture(0),
	m_width(width),
	m_height(height)
{
	m_bodyDefinition->type = convertToBox2DBodyType(bodyType);
	m_bodyDefinition->position.Set(position.getX() + width/2, position.getY() + height/2);
	m_body = simulator.createBody(*m_bodyDefinition);
	m_shape->SetAsBox(width/2, height/2);
	m_fixture = m_body->CreateFixture(m_shape, 0);
}

PhysicalObject::~PhysicalObject()
{
	m_simulator.destroyBody(m_body);
	delete m_shape;
	delete m_bodyDefinition;
}

Point PhysicalObject::getPosition() const
{
	b2Vec2 positionVec = m_body->GetPosition();
	return Point(positionVec.x - m_width/2, positionVec.y - m_height/2);
}

Point PhysicalObject::getCenterPosition() const
{
	b2Vec2 position = m_body->GetPosition();
	Point pointposition(position.x, position.y);
	return pointposition;
}

void PhysicalObject::setCollisionGroup(int16_t collisionGroup)
{
	b2Filter filter = m_fixture->GetFilterData();
	filter.groupIndex = collisionGroup;
	m_fixture->SetFilterData(filter);
}

void PhysicalObject::collideWith(int16_t collisionGroup)
{
	b2Filter filter = m_fixture->GetFilterData();
	filter.maskBits = filter.maskBits | collisionGroup;
	m_fixture->SetFilterData(filter);
}

void PhysicalObject::doNotCollideWith(int16_t collisionGroup)
{
	b2Filter filter = m_fixture->GetFilterData();
	filter.maskBits = filter.maskBits & ~collisionGroup;
	m_fixture->SetFilterData(filter);
}

b2Body &PhysicalObject::getBody()
{
	return *m_body;
}

const b2Body &PhysicalObject::getBody() const
{
	return *m_body;
}
