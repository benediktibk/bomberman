#ifndef PHYSIC_PHYSICALOBJECT_H
#define PHYSIC_PHYSICALOBJECT_H

#include "common/point.h"
#include <stdint.h>

class b2BodyDef;
class b2PolygonShape;
class b2Body;
class b2FixtureDef;
class b2Fixture;

namespace Physic
{
class PhysicSimulator;

class PhysicalObject
{
public:
	enum BodyType
	{
		BodyTypeStatic,
		BodyTypeDynamic
	};

	PhysicalObject(PhysicSimulator &simulator, const Common::Point &position, double width, double height, BodyType bodyType);
	virtual ~PhysicalObject();

	Common::Point getPosition() const;
	Common::Point getCenterPosition() const;
	void setCollisionGroup(int16_t collisionGroup);
	void resetCollisionGroup();
	int16_t getCollisionGroup() const;

protected:
	b2Body& getBody();
	const b2Body& getBody() const;

private:
	PhysicSimulator &m_simulator;
	b2BodyDef *m_bodyDefinition;
	b2Body *m_body;
	b2PolygonShape *m_shape;
	b2Fixture *m_fixture;
	double m_width;
	double m_height;
};
}

#endif
