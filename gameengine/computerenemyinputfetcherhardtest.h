#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHERHARDTEST_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHERHARDTEST_H

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
	class ComputerEnemyInputFetcherHard;

	class ComputerEnemyInputFetcherHardTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ComputerEnemyInputFetcherHardTest);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesideLooseFieldButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed);
		CPPUNIT_TEST(getInputState_movingToFieldRightBesideLooseFieldCloseEnoughToPlaceBomb_spaceKeyPressed);
		CPPUNIT_TEST(getInputState_onDangerousFieldAndShortestWayOutLeftAndRightOtherPlayerAndDownLooseWall_leftKeyPressed);
		CPPUNIT_TEST(getInputState_looseWallRightAndOtherPlayerUp_upKeyPressed);
		CPPUNIT_TEST(getInputState_looseWallRight_rightKeyPressed);
		CPPUNIT_TEST(getInputState_powerUpOnDangerousField_noMovementButtonPressed);
		CPPUNIT_TEST(getInputState_onSaveFieldAsPossibleTargetToBlowUpWallButCantEscapeDirect_spaceKeyNotPressed);
		CPPUNIT_TEST(getInputState_besideSaveFieldAsPossibleTargetToBlowUpWallButCantEscapeDirect_noMovementButtonPressed);
		CPPUNIT_TEST(getInputState_besideSaveFieldAsPossibleTargetToBlowUpEnemyButCantEscapeDirect_noMovementButtonPressed);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	public:
		void getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed();
		void getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed();
		void getInputState_movingToFieldRightBesideLooseFieldButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed();
		void getInputState_movingToFieldRightBesideLooseFieldCloseEnoughToPlaceBomb_spaceKeyPressed();
		void getInputState_onDangerousFieldAndShortestWayOutLeftAndRightOtherPlayerAndDownLooseWall_leftKeyPressed();
		void getInputState_looseWallRightAndOtherPlayerUp_upKeyPressed();
		void getInputState_looseWallRight_rightKeyPressed();
		void getInputState_powerUpOnDangerousField_noMovementButtonPressed();
		void getInputState_onSaveFieldAsPossibleTargetToBlowUpWallButCantEscapeDirect_spaceKeyNotPressed();
		void getInputState_besideSaveFieldAsPossibleTargetToBlowUpWallButCantEscapeDirect_noMovementButtonPressed();
		void getInputState_besideSaveFieldAsPossibleTargetToBlowUpEnemyButCantEscapeDirect_noMovementButtonPressed();

	private:
		void createInputFetcher(const Common::LevelDefinition &level);

	private:
		Common::UniqueIdCreator *m_playerIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::UniqueIdCreator *m_bombIdCreator;
		Common::UniqueIdCreator *m_powerUpIdCreator;
		Common::Grid *m_grid;
		Common::GameState *m_gameState;
		ComputerEnemyInputFetcherHard *m_inputFetcher;
		Common::PlayerState *m_ownPlayer;
		Common::PlayerState *m_otherPlayer;
	};
}

#endif
