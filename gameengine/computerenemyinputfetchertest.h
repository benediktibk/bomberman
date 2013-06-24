#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHERTEST_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class Grid;
	class GameState;
	class UniqueIdCreator;
	class PlayerState;
	class LevelDefinition;
}

namespace GameEngine
{
	class ComputerEnemyInputFetcher;

	class ComputerEnemyInputFetcherTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ComputerEnemyInputFetcherTest);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesideLooseFieldButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesideLooseFieldCloseEnoughToPlaceBomb_spaceKeyPressed);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	public:
		void getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed();
		void getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed();
		void getInputState_movingToFieldRightBesideLooseFieldButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed();
		void getInputState_movingToFieldRightBesideLooseFieldCloseEnoughToPlaceBomb_spaceKeyPressed();

	private:
		void createInputFetcher(const Common::LevelDefinition &level);

	private:
		Common::UniqueIdCreator *m_playerIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::Grid *m_grid;
		Common::GameState *m_gameState;
		ComputerEnemyInputFetcher *m_inputFetcher;
		Common::PlayerState *m_ownPlayer;
		Common::PlayerState *m_otherPlayer;
	};
}

#endif
