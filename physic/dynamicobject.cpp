#include "dynamicobject.h"
#include "physicsimulator.h"
#include "Box2D/Box2D.h"

using namespace Physic;
using namespace Common;

DynamicObject::DynamicObject(PhysicSimulator &simulator, const Point &position, double width, double height) :
	PhysicalObject(simulator, position, width, height, PhysicalObject::BodyTypeDynamic)
{ }

DynamicObject::~DynamicObject()
{ }

void DynamicObject::applyLinearVelocity(double velocityx, double velocityy)
{
	b2Vec2 vel;
	vel.x = velocityx;
	vel.y = velocityy;
	getBody().SetLinearVelocity(vel);
}

double DynamicObject::getVelocityX() const
{
	return getBody().GetLinearVelocity().x;
}

double DynamicObject::getVelocityY() const
{
	return getBody().GetLinearVelocity().y;
}
