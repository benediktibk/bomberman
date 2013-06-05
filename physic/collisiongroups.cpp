#include "collisiongroups.h"
#include "common/playerstate.h"

using namespace Physic;
using namespace std;

CollisionGroups::CollisionGroups(const vector<unsigned int> &playerIds) :
	m_collisionGroupForWalls(1)
{
	for (size_t i = 0; i < playerIds.size(); ++i)
		m_playerIDToCollisionGroup.insert(pair<unsigned int, unsigned int>(i, i+2));
}

int16_t CollisionGroups::getCollisionGroupForPlayer(const Common::PlayerState &player) const
{
	unsigned int collisionGroupNumber = m_playerIDToCollisionGroup.at(player.getId());
	return convertNumberToBitMask(collisionGroupNumber);
}

int16_t CollisionGroups::getCollisionGroupForWall() const
{
	return m_collisionGroupForWalls;
}

int16_t CollisionGroups::convertNumberToBitMask(unsigned int value) const
{
	int16_t result = 1;

	for (unsigned int i = 0; i < value; ++i)
		result *= 2;

	return result;
}
