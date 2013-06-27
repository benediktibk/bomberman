#include "physic/wall.h"
#include "physic/staticobject.h"
#include "common/wallstate.h"

using namespace Physic;
using namespace Common;

Wall::Wall(PhysicSimulator &simulator, const WallState &wall) :
	m_object(new StaticObject(simulator, wall.getPosition(), wall.getDimension(), wall.getDimension()))
{ }

Wall::~Wall()
{
	delete m_object;
}
