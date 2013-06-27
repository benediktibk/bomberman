#include "common/explodedbombstatetest.h"
#include "common/explodedbombstate.h"
#include "common/uniqueidcreator.h"
#include "common/bombstate.h"

using namespace Common;

void ExplodedBombStateTest::constructor_validBombState_lifeTimeIsGreaterThanZero()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 1);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT(explodedBomb.getLifeTime() > 0);
}

void ExplodedBombStateTest::constructor_bombAtPosition4And5_positionIs4And5()
{
	BombState bomb(*m_bombIdCreator, 0, Point(4, 5), 1);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT(Point(4, 5).fuzzyEqual(explodedBomb.getPosition(), 0.0001));
}

void ExplodedBombStateTest::decreaseLifeTime_03_lifeTimeIs03Smaller()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 1);
	ExplodedBombState explodedBomb(bomb);
	double oldLifeTime = explodedBomb.getLifeTime();

	explodedBomb.decreaseLifeTime(0.3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(oldLifeTime - 0.3, explodedBomb.getLifeTime(), 0.0001);
}

void ExplodedBombStateTest::decreaseLifeTime_4_hasChanged()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 1);
	ExplodedBombState explodedBomb(bomb);
	explodedBomb.resetChanged();

	explodedBomb.decreaseLifeTime(4);

	CPPUNIT_ASSERT(explodedBomb.hasChanged());
}

void ExplodedBombStateTest::constructor_bombWithDestructionRange3_maximumDestructionRangeIs3()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, explodedBomb.getMaximumDestructionRange());
}

void ExplodedBombStateTest::setDestroyedIfNoLifeTimeLeft_lifeTimeGreaterZero_notDestroyed()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 1);
	ExplodedBombState explodedBomb(bomb);

	explodedBomb.setDestroyedIfNoLifeTimeLeft();

	CPPUNIT_ASSERT(!explodedBomb.isDestroyed());
}

void ExplodedBombStateTest::setDestroyedIfNoLifeTimeLeft_lifeTimeSmallerZero_destroyed()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 1);
	ExplodedBombState explodedBomb(bomb);
	double initialLifeTime = explodedBomb.getLifeTime();
	explodedBomb.decreaseLifeTime(initialLifeTime*2);

	explodedBomb.setDestroyedIfNoLifeTimeLeft();

	CPPUNIT_ASSERT(explodedBomb.isDestroyed());
}

void ExplodedBombStateTest::constructor_bombWithCertainDimension_dimensionIsTheSame()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 1);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(bomb.getDimension(), explodedBomb.getDimension(), 0.0001);
}

void ExplodedBombStateTest::constructor_maximumDestructionRange3_destructionRangeLeftIs3()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, explodedBomb.getDestructionRangeLeft());
}

void ExplodedBombStateTest::constructor_maximumDestructionRange3_destructionRangeUpIs3()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, explodedBomb.getDestructionRangeUp());
}

void ExplodedBombStateTest::constructor_maximumDestructionRange3_destructionRangeRightIs3()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, explodedBomb.getDestructionRangeRight());
}

void ExplodedBombStateTest::constructor_maximumDestructionRange3_destructionRangeDownIs3()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, explodedBomb.getDestructionRangeDown());
}

void ExplodedBombStateTest::setDestructionRangeLeft_2_destructionRangeLeftIs2()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	explodedBomb.setDestructionRangeLeft(2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeLeft());
}

void ExplodedBombStateTest::setDestructionRangeUp_2_destructionRangeUpIs2()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	explodedBomb.setDestructionRangeUp(2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeUp());
}

void ExplodedBombStateTest::setDestructionRangeRight_2_destructionRangeRightIs2()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	explodedBomb.setDestructionRangeRight(2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeRight());
}

void ExplodedBombStateTest::setDestructionRangeDown_2_destructionRangeDownIs2()
{
	BombState bomb(*m_bombIdCreator, 0, Point(), 3);
	ExplodedBombState explodedBomb(bomb);

	explodedBomb.setDestructionRangeDown(2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeDown());
}

void ExplodedBombStateTest::setUp()
{
	delete m_bombIdCreator;
	m_bombIdCreator = new UniqueIdCreator();
}

void ExplodedBombStateTest::tearDown()
{
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
}
