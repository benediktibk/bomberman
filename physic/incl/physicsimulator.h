#ifndef PHYSICSIMULATOR_H
#define PHYSICSIMULATOR_H

class b2World;
class b2Vec2;
class b2Body;
class b2BodyDef;

namespace Physic
{
class PhysicSimulator
{
public:
	PhysicSimulator();
	~PhysicSimulator();

	b2Body* createBody(const b2BodyDef &definition);

private:
	b2Vec2 *m_gravity;
	b2World *m_world;
};
}

#endif
