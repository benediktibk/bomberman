#include "bombstatetest.h"
#include "bombstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void BombStateTest::constructor_positionIs5And4_positionIs5And4()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(5, 4), 1);

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), bomb.getPosition());
}

void BombStateTest::setLifeTime_3_lifeTimeIs3()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(), 1);

	bomb.setLifeTime(3);

	CPPUNIT_ASSERT_EQUAL(3.0, bomb.getLifeTime());
}

void BombStateTest::constructor_destructionRangeIs5_DestructionRangeIs5()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(), 5);

	CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(5), bomb.getDestructionRange());
}

void BombStateTest::setLifeTime_4_hasChanged()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(), 1);
	bomb.resetChanged();

	bomb.setLifeTime(4);

	CPPUNIT_ASSERT(bomb.hasChanged());
}

void BombStateTest::setDestroyed_empty_hasChanged()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(), 1);
	bomb.resetChanged();

	bomb.setDestroyed();

	CPPUNIT_ASSERT(bomb.hasChanged());
}

void BombStateTest::getBombHeight_heightIs1()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(), 1);

	CPPUNIT_ASSERT_EQUAL(1.0, bomb.getHeight());
}

void BombStateTest::constructor_playerIDIs5_playerIDIs5()
{
	UniqueIdCreator id;
	BombState bomb(id, 5, Point(), 1);

	CPPUNIT_ASSERT_EQUAL((unsigned int)5, bomb.getPlayerID());
}

void BombStateTest::getBombWidth_widthIs1()
{
	UniqueIdCreator id;
	BombState bomb(id, 0, Point(), 1);

	CPPUNIT_ASSERT_EQUAL(1.0, bomb.getWidth());
}
