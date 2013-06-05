#ifndef PHYSIC_COLLISIONGROUPSTEST_H
#define PHYSIC_COLLISIONGROUPSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "common/uniqueidcreator.h"

namespace Physic
{
class CollisionGroupsTest :
		public CPPUNIT_NS::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(CollisionGroupsTest);
	CPPUNIT_TEST(constructor_noPlayer_collisionGroupForWallIsNotZero);
	CPPUNIT_TEST(constructor_onePlayer_collisionGroupForWallIsDifferentToPlayerCollisionGroup);
	CPPUNIT_TEST(constructor_twoPlayers_collisionGroupsForPlayersAreDifferent);
	CPPUNIT_TEST(getCollisionGroupForWall_empty_isPowerOf2);
	CPPUNIT_TEST(getCollisionGroupForPlayer_onePlayer_isPowerOf2);
	CPPUNIT_TEST(getCollisionGroupForPlayer_secondPlayer_isPowerOf2);
	CPPUNIT_TEST_SUITE_END();

private:
	void constructor_noPlayer_collisionGroupForWallIsNotZero();
	void constructor_onePlayer_collisionGroupForWallIsDifferentToPlayerCollisionGroup();
	void constructor_twoPlayers_collisionGroupsForPlayersAreDifferent();
	void getCollisionGroupForWall_empty_isPowerOf2();
	void getCollisionGroupForPlayer_onePlayer_isPowerOf2();
	void getCollisionGroupForPlayer_secondPlayer_isPowerOf2();

private:
	bool isPowerOfTwo(double value) const;

private:
	Common::UniqueIdCreator m_idCreator;
};
}

#endif
