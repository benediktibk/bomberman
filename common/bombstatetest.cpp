#include "bombstatetest.h"
#include "bombstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void BombStateTest::setPosition_5And4_positionIs5And4()
{
	UniqueIdCreator id;
	BombState bomb(id);

	bomb.setPosition(Point(5, 4));

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), bomb.getPosition());
}

void BombStateTest::setLifeTime_3_lifeTimeIs3()
{
	UniqueIdCreator id;
	BombState bomb(id);

	bomb.setLifeTime(3);

	CPPUNIT_ASSERT_EQUAL(3.0, bomb.getLifeTime());
}
void BombStateTest::setDestructionRange_5_DestructionRangeIs5()
{
	UniqueIdCreator id;
	BombState bomb(id);

	bomb.setDestructionRange(5);

	CPPUNIT_ASSERT_EQUAL(5, bomb.getDestructionRange());
}

void BombStateTest::setPosition_5And4_hasChanged()
{
	UniqueIdCreator id;
	BombState bomb(id);
	bomb.resetChanged();

	bomb.setPosition(Point(5, 4));

	CPPUNIT_ASSERT(bomb.hasChanged());
}

void BombStateTest::setLifeTime_4_hasChanged()
{
	UniqueIdCreator id;
	BombState bomb(id);
	bomb.resetChanged();

	bomb.setLifeTime(4);

	CPPUNIT_ASSERT(bomb.hasChanged());
}

void BombStateTest::setDestructionRange_5_hasChanged()
{
	UniqueIdCreator id;
	BombState bomb(id);
	bomb.resetChanged();

	bomb.setDestructionRange(5);

	CPPUNIT_ASSERT(bomb.hasChanged());
}

void BombStateTest::setDestroyed_empty_hasChanged()
{
	UniqueIdCreator id;
	BombState bomb(id);
	bomb.resetChanged();

	bomb.setDestroyed();

	CPPUNIT_ASSERT(bomb.hasChanged());
}
