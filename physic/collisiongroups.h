#ifndef PHYSIC_COLLISIONGROUPS_H
#define PHYSIC_COLLISIONGROUPS_H

#include <map>
#include <vector>
#include <stdint.h>

namespace Common
{
	class PlayerState;
}

namespace Physic
{
class CollisionGroups
{
public:
	CollisionGroups(const std::vector<unsigned int> &playerIds);

	int16_t getCollisionGroupForPlayer(const Common::PlayerState &player) const;
	int16_t getCollisionGroupForWall() const;

private:
	int16_t convertNumberToBitMask(unsigned int value) const;

private:
	const unsigned int m_collisionGroupForWalls;
	std::map<unsigned int, unsigned int> m_playerIDToCollisionGroup;
};
}

#endif
