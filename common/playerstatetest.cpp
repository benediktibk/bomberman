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

void PlayerStateTest::countBomb_calledTwice_bombCountIs2()
{
	PlayerState player(*m_idCreator);
	player.setMaxBombs(10);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, player.getBombCount());
}

void PlayerStateTest::reduceBombCount_calledTwiceAndIncreasedThreeTimes_bombCountIs1()
{
	PlayerState player(*m_idCreator);
	player.setMaxBombs(10);

	player.countBomb();
	player.countBomb();
	player.countBomb();
	player.reduceBombCount();
	player.reduceBombCount();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, player.getBombCount());
}

void PlayerStateTest::getRemainingBombs_maxBombCount5And2BombsPlaced_3()
{
	PlayerState player(*m_idCreator);
	player.setMaxBombs(5);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, player.getRemainingBombs());
}

void PlayerStateTest::canPlaceBomb_maxBombCount2AndTwoBombsPlaced_false()
{
	PlayerState player(*m_idCreator);
	player.setMaxBombs(2);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT(!player.canPlayerPlaceBomb());
}

void PlayerStateTest::canPlaceBomb_maxBombCount3AndTwoBombsPlaced_true()
{
	PlayerState player(*m_idCreator);
	player.setMaxBombs(3);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT(player.canPlayerPlaceBomb());
}

void PlayerStateTest::constructor_idCreator_maximumSpeedIs5()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, player.getMaximumSpeed(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_notMoving_0()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_notMoving_0()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::constructor_idCreator_isNotMoving()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT(!player.isMoving());
}

void PlayerStateTest::setMoving_empty_isMoving()
{
	PlayerState player(*m_idCreator);

	player.setMoving();

	CPPUNIT_ASSERT(player.isMoving());
}

void PlayerStateTest::setNotMoving_empty_isNotMoving()
{
	PlayerState player(*m_idCreator);
	player.setMoving();

	player.setNotMoving();

	CPPUNIT_ASSERT(!player.isMoving());
}

void PlayerStateTest::constructor_idCreator_widthIs1()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getWidth(), 0.0001);
}

void PlayerStateTest::constructor_idCreator_heightIs1()
{
	PlayerState player(*m_idCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getHeight(), 0.0001);
}

void PlayerStateTest::getCenterPosition_positionIs3And4_35And45()
{
	PlayerState player(*m_idCreator);
	player.setPosition(Point(3, 4));

	CPPUNIT_ASSERT_EQUAL(Point(3.5, 4.5), player.getCenterPosition());
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionUp_0()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionUp();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionDown_0()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionDown();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionRight_maximumSpeed()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionRight();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(player.getMaximumSpeed(), player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionLeft_minusMaximumSpeed()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionLeft();

	CPPUNIT_ASSERT_DOUBLES_EQUAL((-1)*player.getMaximumSpeed(), player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionUp_maximumSpeed()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionUp();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(player.getMaximumSpeed(), player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionDown_minusMaximumSpeed()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionDown();

	CPPUNIT_ASSERT_DOUBLES_EQUAL((-1)*player.getMaximumSpeed(), player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionLeft_0()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionLeft();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionRight_0()
{
	PlayerState player(*m_idCreator);
	player.setMoving();
	player.setDirectionRight();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoY(), 0.0001);
}


