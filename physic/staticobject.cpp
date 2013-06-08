#include "staticobject.h"

using namespace Physic;
using namespace Common;

StaticObject::StaticObject(PhysicSimulator &simulator, const Point &position, double width, double height) :
	PhysicalObject(simulator, position, width, height, PhysicalObject::BodyTypeStatic)
{ }