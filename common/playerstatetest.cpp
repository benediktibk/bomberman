#include "common/playerstatetest.h"
#include "common/playerstate.h"
#include "common/uniqueidcreator.h"
#include "common/bombstate.h"

using namespace Common;
using namespace std;

void PlayerStateTest::setUp()
{
	m_playerIDCreator = new UniqueIdCreator;
	m_bombIDCreator = new UniqueIdCreator;
}

void PlayerStateTest::tearDown()
{
	delete m_playerIDCreator;
	m_playerIDCreator = 0;
	delete m_bombIDCreator;
	m_bombIDCreator = 0;
}

void PlayerStateTest::constructor_idCreator_idFetched()
{
	PlayerState *player = new PlayerState(*m_playerIDCreator);

	CPPUNIT_ASSERT_EQUAL((size_t)1, m_playerIDCreator->getIDCount());
	delete player;
}

void PlayerStateTest::constructor_validVParameter_destructionRangeIs1()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, player.getDestructionRangeOfNewBombs());
}

void PlayerStateTest::destructor_empty_idCountIsZero()
{
	PlayerState *player = new PlayerState(*m_playerIDCreator);

	delete player;

	CPPUNIT_ASSERT_EQUAL((size_t)0, m_playerIDCreator->getIDCount());
}

void PlayerStateTest::setPosition_4And5_positionIs4And5()
{
	PlayerState player(*m_playerIDCreator);

	player.setPosition(Point(4, 5));

	CPPUNIT_ASSERT_EQUAL(Point(4, 5), player.getPosition());
}

void PlayerStateTest::setDirectionUp_empty_directionIsUp()
{
	PlayerState player(*m_playerIDCreator);

	player.setDirectionUp();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, player.getDirection());
}

void PlayerStateTest::setDirectionDown_empty_directionIsDown()
{
	PlayerState player(*m_playerIDCreator);

	player.setDirectionDown();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, player.getDirection());
}

void PlayerStateTest::setDirectionRight_empty_directionIsRight()
{
	PlayerState player(*m_playerIDCreator);

	player.setDirectionRight();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionRight, player.getDirection());
}

void PlayerStateTest::setDirectionLeft_empty_directionIsLeft()
{
	PlayerState player(*m_playerIDCreator);

	player.setDirectionLeft();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, player.getDirection());
}

void PlayerStateTest::setMaxBombs_4_maxBombsIs4()
{
	PlayerState player(*m_playerIDCreator);

	player.setMaxBombs(4);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, player.getMaxBombs());
}

void PlayerStateTest::constructor_idCreator_maxBombsIs1()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, player.getMaxBombs());
}

void PlayerStateTest::increaseMaxBombs_calledTwice_maxBombsIs3()
{
	PlayerState player(*m_playerIDCreator);

	player.increaseMaxBombs();
	player.increaseMaxBombs();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, player.getMaxBombs());
}

void PlayerStateTest::increaseMaxBombs_5_maxBombsIs6()
{
	PlayerState player(*m_playerIDCreator);

	player.increaseMaxBombs(5);

	CPPUNIT_ASSERT_EQUAL((unsigned int)6, player.getMaxBombs());
}

void PlayerStateTest::countBomb_calledTwice_bombCountIs2()
{
	PlayerState player(*m_playerIDCreator);
	player.setMaxBombs(10);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, player.getBombCount());
}

void PlayerStateTest::reduceBombCount_calledTwiceAndIncreasedThreeTimes_bombCountIs1()
{
	PlayerState player(*m_playerIDCreator);
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
	PlayerState player(*m_playerIDCreator);
	player.setMaxBombs(5);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, player.getRemainingBombs());
}

void PlayerStateTest::canPlaceBomb_maxBombCount2AndTwoBombsPlaced_false()
{
	PlayerState player(*m_playerIDCreator);
	player.setMaxBombs(2);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT(!player.canPlayerPlaceBomb());
}

void PlayerStateTest::canPlaceBomb_maxBombCount3AndTwoBombsPlaced_true()
{
	PlayerState player(*m_playerIDCreator);
	player.setMaxBombs(3);

	player.countBomb();
	player.countBomb();

	CPPUNIT_ASSERT(player.canPlayerPlaceBomb());
}

void PlayerStateTest::constructor_idCreator_maximumSpeedIs5()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, player.getSpeed(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_notMoving_0()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_notMoving_0()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::constructor_idCreator_isNotMoving()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT(!player.isMoving());
}

void PlayerStateTest::constructor_idCreator_dimensionIs1()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, player.getDimension(), 0.0001);
}

void PlayerStateTest::getCenterPosition_positionIs3And4_35And45()
{
	PlayerState player(*m_playerIDCreator);
	player.setPosition(Point(3, 4));

	CPPUNIT_ASSERT_EQUAL(Point(3.5, 4.5), player.getCenterPosition());
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionUp_0()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionUp();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionDown_0()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionDown();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionRight_maximumSpeed()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionRight();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(player.getSpeed(), player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoX_movingAndDirectionLeft_minusMaximumSpeed()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionLeft();

	CPPUNIT_ASSERT_DOUBLES_EQUAL((-1)*player.getSpeed(), player.getSpeedIntoX(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionUp_maximumSpeed()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionUp();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(player.getSpeed(), player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionDown_minusMaximumSpeed()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionDown();

	CPPUNIT_ASSERT_DOUBLES_EQUAL((-1)*player.getSpeed(), player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionLeft_0()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionLeft();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::getSpeedIntoY_movingAndDirectionRight_0()
{
	PlayerState player(*m_playerIDCreator);
	player.setDirectionRight();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, player.getSpeedIntoY(), 0.0001);
}

void PlayerStateTest::doNotCollideWith_validBomb_oneBombNotToCollideWith()
{
	BombState bomb(*m_bombIDCreator, 0, Point(), 1);
	PlayerState player(*m_playerIDCreator);

	player.doNotCollideWith(&bomb);

	vector<const BombState*> result = player.getBombsNotToCollideWith();
	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
}

void PlayerStateTest::doNotCollideWith_twoBombsRightBeside_twoBombsNotToCollideWith()
{
	BombState bombOne(*m_bombIDCreator, 0, Point(), 1);
	BombState bombTwo(*m_bombIDCreator, 0, Point(), 1);
	PlayerState player(*m_playerIDCreator);

	player.doNotCollideWith(&bombOne);
	player.doNotCollideWith(&bombTwo);

	vector<const BombState*> result = player.getBombsNotToCollideWith();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void PlayerStateTest::removeBombFromDoNotCollideList_twoBombsAddedAndFirstOneExploded_oneBombNotToCollideWith()
{
	BombState bombOne(*m_bombIDCreator, 0, Point(1, 2), 1);
	BombState bombTwo(*m_bombIDCreator, 0, Point(1, 3), 1);
	PlayerState player(*m_playerIDCreator);
	player.setPosition(Point(1, 2.5));
	player.doNotCollideWith(&bombOne);
	player.doNotCollideWith(&bombTwo);
	bombOne.setDestroyed();

	player.removeBombFromDoNotCollideList(&bombOne);

	vector<const BombState*> result = player.getBombsNotToCollideWith();
	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
}

void PlayerStateTest::increaseSpeed_defaultSpeed_speedIncreased()
{
	PlayerState player(*m_playerIDCreator);
	double initialSpeed = player.getSpeed();

	player.increaseSpeed();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(initialSpeed + player.getSpeedIncrement(), player.getSpeed(), 0.001);
}

void PlayerStateTest::setDestructionRangeOfNewBombs_4_destructionRangeIs4()
{
	PlayerState player(*m_playerIDCreator);

	player.setDestructionRangeOfNewBombs(4);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, player.getDestructionRangeOfNewBombs());
}

void PlayerStateTest::constructor_idCreator_speedIncrementIs05()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, player.getSpeedIncrement(), 0.00001);
}

void PlayerStateTest::constructor_idCreator_speedIncrementIsGreaterZero()
{
	PlayerState player(*m_playerIDCreator);

	CPPUNIT_ASSERT(player.getSpeedIncrement() > 0);
}
