#ifndef PHYSIC_STATICOBJECT_H
#define PHYSIC_STATICOBJECT_H

#include "physic/physicalobject.h"

namespace Physic
{
class StaticObject :
		public PhysicalObject
{
public:
	StaticObject(PhysicSimulator &simulator, const Common::Point &position, double width, double height);
};
}

#endif
