#ifndef PHYSIC_STATICOBJECT_H
#define PHYSIC_STATICOBJECT_H

#include "common/point.h"

class b2Body;
class b2BodyDef;
class b2PolygonShape;
class b2FixtureDef;
class b2Fixture;

namespace Physic
{
class PhysicSimulator;

class StaticObject
{
public:
	StaticObject(PhysicSimulator &simulator, const Common::Point &position, double width, double height);
	~StaticObject();

	void setPosition(const Common::Point &point);

private:
	PhysicSimulator &m_simulator;
	b2Body *m_body;
	b2BodyDef *m_bodyDef;
	b2Fixture *m_fixture;
	b2FixtureDef *m_fixtureDef;
	b2PolygonShape *m_shape;
	double m_width;
	double m_height;
};
}

#endif
