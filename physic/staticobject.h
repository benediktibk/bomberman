#ifndef STATICOBJECT_H
#define STATICOBJECT_H

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
    StaticObject(PhysicSimulator &simulator, const Common::Point &position, const Common::Point &size);
    ~StaticObject();

    void SetPosition(double x, double y);
    //void StaticObject::DestroyBody();

private:

    b2Body *m_body;
    b2BodyDef *m_bodyDef;
    b2Fixture *m_fixture;
    b2FixtureDef *m_fixtureDef;
    b2PolygonShape *m_shape;
    double m_x;
    double m_y;
};
}

#endif
