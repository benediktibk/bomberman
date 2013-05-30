#ifndef PHYSIC_PHYSICSIMULATOR_H
#define PHYSIC_PHYSICSIMULATOR_H

#include <sys/types.h>

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
	void destroyBody(b2Body *body);
	void simulateStep(double time);
	size_t getBodyCount() const;

private:
	b2Vec2 *m_gravity;
	b2World *m_world;
	int m_velocityIterations;
	int m_positionIterations;
	size_t m_bodyCount;
	double m_maximumTimeStep;
};
}

#endif
