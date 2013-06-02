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
	DynamicObject(PhysicSimulator &simulator, const Common::Point &position, double width, double height);
	~DynamicObject();

	Common::Point getPosition() const;
	Common::Point getCenterPosition() const;
	void applyLinearVelocity(double velocityx, double velocityy);
	double getVelocityX() const;
	double getVelocityY() const;

private:
	PhysicSimulator &m_simulator;
	b2BodyDef *m_bodyDefinition;
	b2Body *m_body;
	b2PolygonShape *m_shape;
	b2FixtureDef *m_fixtureDefinition;
	b2Fixture *m_fixture;
	double m_width;
	double m_height;
};
}

#endif
