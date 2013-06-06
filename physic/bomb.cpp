#include "physic/bomb.h"
#include "physic/staticobject.h"
#include "common/bombstate.h"
#include "common/playerstate.h"

using namespace Physic;
using namespace Common;

Bomb::Bomb(PhysicSimulator &simulator, const Common::BombState &bomb) :
	m_object(new StaticObject(simulator, bomb.getPosition(), bomb.getWidth(), bomb.getHeight()))
{ }

Bomb::~Bomb()
{
	delete m_object;
}

void Bomb::doNotCollideWith(const PlayerState &player)
{
	int16_t playerId = player.getId();
	int16_t collisionGroup = (-1)*(playerId + 1);
	m_object->setCollisionGroup(collisionGroup);
}

void Bomb::collideWithEverything()
{
	m_object->resetCollisionGroup();
}
