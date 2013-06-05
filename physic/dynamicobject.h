#ifndef PHYSIC_DYNAMICOBJECT_H
#define PHYSIC_DYNAMICOBJECT_H

#include "physic/physicalobject.h"

namespace Physic
{
class DynamicObject :
		public PhysicalObject
{
public:
	DynamicObject(PhysicSimulator &simulator, const Common::Point &position, double width, double height);
	virtual ~DynamicObject();

	void applyLinearVelocity(double velocityx, double velocityy);
	double getVelocityX() const;
	double getVelocityY() const;
};
}

#endif
