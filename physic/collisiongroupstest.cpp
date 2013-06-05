#include "collisiongroupstest.h"
#include "collisiongroups.h"
#include "common/playerstate.h"
#include <math.h>

using namespace Physic;
using namespace Common;
using namespace std;

void CollisionGroupsTest::constructor_noPlayer_collisionGroupForWallIsNotZero()
{
	vector<unsigned int> playerIDs;

	CollisionGroups groups(playerIDs);

	CPPUNIT_ASSERT(groups.getCollisionGroupForWall() != 0);
}

void CollisionGroupsTest::constructor_onePlayer_collisionGroupForWallIsDifferentToPlayerCollisionGroup()
{
	vector<unsigned int> playerIDs;
	PlayerState player(m_idCreator);
	playerIDs.push_back(player.getId());

	CollisionGroups groups(playerIDs);

	CPPUNIT_ASSERT(groups.getCollisionGroupForPlayer(player) != groups.getCollisionGroupForWall());
}

void CollisionGroupsTest::constructor_twoPlayers_collisionGroupsForPlayersAreDifferent()
{
	vector<unsigned int> playerIDs;
	PlayerState playerOne(m_idCreator);
	PlayerState playerTwo(m_idCreator);
	playerIDs.push_back(playerOne.getId());
	playerIDs.push_back(playerTwo.getId());

	CollisionGroups groups(playerIDs);

	CPPUNIT_ASSERT(groups.getCollisionGroupForPlayer(playerOne) != groups.getCollisionGroupForPlayer(playerTwo));
}

void CollisionGroupsTest::getCollisionGroupForWall_empty_isPowerOf2()
{
	vector<unsigned int> playerIDs;
	CollisionGroups groups(playerIDs);

	int16_t collisionGroup = groups.getCollisionGroupForWall();

	CPPUNIT_ASSERT(isPowerOfTwo(collisionGroup));
}

void CollisionGroupsTest::getCollisionGroupForPlayer_onePlayer_isPowerOf2()
{
	vector<unsigned int> playerIDs;
	PlayerState player(m_idCreator);
	playerIDs.push_back(player.getId());
	CollisionGroups groups(playerIDs);

	int16_t collisionGroup = groups.getCollisionGroupForPlayer(player);

	CPPUNIT_ASSERT(isPowerOfTwo(collisionGroup));
}

void CollisionGroupsTest::getCollisionGroupForPlayer_secondPlayer_isPowerOf2()
{
	vector<unsigned int> playerIDs;
	PlayerState playerOne(m_idCreator);
	PlayerState playerTwo(m_idCreator);
	playerIDs.push_back(playerOne.getId());
	playerIDs.push_back(playerTwo.getId());
	CollisionGroups groups(playerIDs);

	int16_t collisionGroup = groups.getCollisionGroupForPlayer(playerTwo);

	CPPUNIT_ASSERT(isPowerOfTwo(collisionGroup));
}

bool CollisionGroupsTest::isPowerOfTwo(double value) const
{
	double exponent = log(value)/log(2);
	double exponentFloored = floor(exponent);

	return fabs(exponent - exponentFloored) < 0.001;
}
