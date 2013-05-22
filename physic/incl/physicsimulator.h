#ifndef PHYSICSIMULATOR_H
#define PHYSICSIMULATOR_H

class b2World;
class b2Vec2;

namespace Physic
{
class PhysicSimulator
{
public:
	PhysicSimulator();
	~PhysicSimulator();

private:
	b2Vec2 *m_gravity;
	b2World *m_world;
};
}

#endif
