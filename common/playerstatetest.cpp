#include "common/playerstatetest.h"
#include "common/playerstate.h"
#include "common/uniqueidcreator.h"

using namespace Common;

void PlayerStateTest::setUp()
{
	m_idCreator = new UniqueIdCreator;
}

void PlayerStateTest::tearDown()
{
	delete m_idCreator;
}

void PlayerStateTest::constructor_idCreator_idFetched()
{
	PlayerState *player = new PlayerState(*m_idCreator);

	CPPUNIT_ASSERT_EQUAL((size_t)1, m_idCreator->getIDCount());
	delete player;
}

void PlayerStateTest::destructor_empty_idCountIsZero()
{
	PlayerState *player = new PlayerState(*m_idCreator);

	delete player;

	CPPUNIT_ASSERT_EQUAL((size_t)0, m_idCreator->getIDCount());
}

void PlayerStateTest::setPosition_4And5_positionIs4And5()
{
	PlayerState player(*m_idCreator);

	player.setPosition(Point(4, 5));

	CPPUNIT_ASSERT_EQUAL(Point(4, 5), player.getPosition());
}

void PlayerStateTest::setDirectionUp_empty_directionIsUp()
{
	PlayerState player(*m_idCreator);

	player.setDirectionUp();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, player.getDirection());
}

void PlayerStateTest::setDirectionDown_empty_directionIsDown()
{
	PlayerState player(*m_idCreator);

	player.setDirectionDown();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, player.getDirection());
}

void PlayerStateTest::setDirectionRight_empty_directionIsRight()
{
	PlayerState player(*m_idCreator);

	player.setDirectionRight();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionRight, player.getDirection());
}

void PlayerStateTest::setDirectionLeft_empty_directionIsLeft()
{
	PlayerState player(*m_idCreator);

	player.setDirectionLeft();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, player.getDirection());
}

void PlayerStateTest::setMaxBombs_4_maxBombsIs4()
{
	PlayerState player(*m_idCreator);

	player.setMaxBombs(4);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, player.getMaxBombs());
}

void PlayerStateTest::constructor_idCreator_maxBombsIs1()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, player.getMaxBombs());
}

void PlayerStateTest::increaseMaxBombs_calledTwice_maxBombsIs3()
{
	PlayerState player(*m_idCreator);

	player.increaseMaxBombs();
	player.increaseMaxBombs();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, player.getMaxBombs());
}

void PlayerStateTest::increaseMaxBombs_5_maxBombsIs6()
{
	PlayerState player(*m_idCreator);

	player.increaseMaxBombs(5);

	CPPUNIT_ASSERT_EQUAL((unsigned int)6, player.getMaxBombs());
}


