#ifndef PHYSIC_GAMEPHYSICSIMULATORTEST_H
#define PHYSIC_GAMEPHYSICSIMULATORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "common/uniqueidcreator.h"

namespace Physic
{
	class GamePhysicSimulatorTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE(GamePhysicSimulatorTest);
		CPPUNIT_TEST(simulateStep_movePlayerTowardsWall_playerCollidesWithWall);
		CPPUNIT_TEST(simulateStep_movePlayerTowardsBomb_playerCollidesWithBomb);
		CPPUNIT_TEST(simulateStep_twoPlayersAndOneMovesTowardsTheOther_playersCollide);
		CPPUNIT_TEST(simulateStep_twoPlayersAndOneMovesTowardsTheOther_playerTwoDoesntMove);
		CPPUNIT_TEST_SUITE_END();

	private:
		void simulateStep_movePlayerTowardsWall_playerCollidesWithWall();
		void simulateStep_movePlayerTowardsBomb_playerCollidesWithBomb();
		void simulateStep_twoPlayersAndOneMovesTowardsTheOther_playersCollide();
		void simulateStep_twoPlayersAndOneMovesTowardsTheOther_playerTwoDoesntMove();

	private:
		Common::UniqueIdCreator m_playerIDCreator;
		Common::UniqueIdCreator m_wallIDCreator;
		Common::UniqueIdCreator m_bombIDCreator;
	};
}

#endif
