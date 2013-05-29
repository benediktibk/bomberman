#ifndef PHYSIC_DYNAMICOBJECT_H
#define PHYSIC_DYNAMICOBJECT_H

#include "common/point.h"

class b2Body;
class b2BodyDef;
class b2PolygonShape;
class b2FixtureDef;
class b2Fixture;

namespace Physic
{
class PhysicSimulator;

class DynamicObject
{
public:
	DynamicObject(PhysicSimulator &simulator);
	~DynamicObject();

	Common::Point getPosition() const;
	void applyLinearVelocity(double velocityx, double velocityy);

private:
	b2BodyDef *m_bodyDefinition;
	b2Body *m_body;
	b2PolygonShape *m_shape;
	b2FixtureDef *m_fixtureDefinition;
	b2Fixture *m_fixture;
};
}

#endif
