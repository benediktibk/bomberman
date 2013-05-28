#ifndef PHYSIC_STATICOBJECT_H
#define PHYSIC_STATICOBJECT_H
#include "point.h"

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
    StaticObject(PhysicSimulator &simulator);
    ~StaticObject();

    Common::Point getPosition() const;
    void applyLinearVelocity(double velocityx,double velocityy);
private:

    b2Body *m_body;
    b2BodyDef *m_bodyDef;
    b2Fixture *m_fixture;
    b2FixtureDef *m_fixtureDef;
    b2PolygonShape *m_shape;
};
}

#endif
