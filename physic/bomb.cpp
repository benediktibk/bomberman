#include "physic/bomb.h"
#include "physic/staticobject.h"
#include "common/bombstate.h"

using namespace Physic;
using namespace Common;

Bomb::Bomb(PhysicSimulator &simulator, const Common::BombState &bomb) :
	m_object(new StaticObject(simulator, bomb.getPosition(), bomb.getWidth(), bomb.getHeight()))
{ }

Bomb::~Bomb()
{
	delete m_object;
}
