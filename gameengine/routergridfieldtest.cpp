#include "gameengine/routergridfieldtest.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;
using namespace Common;

void RouterGridFieldTest::constructor_empty_isNotSolidWall()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(!field.isSolidWall());
}

void RouterGridFieldTest::constructor_empty_isNotLooseWall()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(!field.isLooseWall());
}

void RouterGridFieldTest::constructor_empty_isNotBomb()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(!field.isBomb());
}

void RouterGridFieldTest::constructor_empty_isNotPlayer()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(!field.isPlayer());
}

void RouterGridFieldTest::constructor_empty_isNotDangerous()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(!field.isDangerous());
}

void RouterGridFieldTest::constructor_empty_isNotPowerUp()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(!field.isPowerUp());
}

void RouterGridFieldTest::setSolidWall_true_isSolidWall()
{
	RouterGridField field(GridPoint(5, 6));

	field.setSolidWall(true);

	CPPUNIT_ASSERT(field.isSolidWall());
}

void RouterGridFieldTest::setLooseWall_true_isLooseWall()
{
	RouterGridField field(GridPoint(5, 6));

	field.setLooseWall(true);

	CPPUNIT_ASSERT(field.isLooseWall());
}

void RouterGridFieldTest::setBomb_true_isBomb()
{
	RouterGridField field(GridPoint(5, 6));

	field.setBomb(true);

	CPPUNIT_ASSERT(field.isBomb());
}

void RouterGridFieldTest::setBomb_true_isDangerous()
{
	RouterGridField field(GridPoint(5, 6));

	field.setBomb(true);

	CPPUNIT_ASSERT(field.isDangerous());
}

void RouterGridFieldTest::setPlayer_true_isPlayer()
{
	RouterGridField field(GridPoint(5, 6));

	field.setPlayer(true);

	CPPUNIT_ASSERT(field.isPlayer());
}

void RouterGridFieldTest::setDangerous_true_isDangerous()
{
	RouterGridField field(GridPoint(5, 6));

	field.setDangerous(true);

	CPPUNIT_ASSERT(field.isDangerous());
}

void RouterGridFieldTest::setPowerUp_true_isPowerUp()
{
	RouterGridField field(GridPoint(5, 6));

	field.setPowerUp(true);

	CPPUNIT_ASSERT(field.isPowerUp());
}

void RouterGridFieldTest::isFree_nothingSet_true()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(field.isFree());
}

void RouterGridFieldTest::isFree_bombSet_false()
{
	RouterGridField field(GridPoint(5, 6));

	field.setBomb(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_playerSet_false()
{
	RouterGridField field(GridPoint(5, 6));

	field.setPlayer(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_looseWallSet_false()
{
	RouterGridField field(GridPoint(5, 6));

	field.setLooseWall(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_solidWallSet_false()
{
	RouterGridField field(GridPoint(5, 6));

	field.setSolidWall(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_dangerousSet_true()
{
	RouterGridField field(GridPoint(5, 6));

	field.setDangerous(true);

	CPPUNIT_ASSERT(field.isFree());
}

void RouterGridFieldTest::isFree_powerUpSet_true()
{
	RouterGridField field(GridPoint(5, 6));

	field.setPowerUp(true);

	CPPUNIT_ASSERT(field.isFree());
}

void RouterGridFieldTest::constructor_5And6_positionIs5And6()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT_EQUAL(GridPoint(5, 6), field.getPosition());
}

void RouterGridFieldTest::constructor_5And6_isValid()
{
	RouterGridField field(GridPoint(5, 6));

	CPPUNIT_ASSERT(field.isValid());
}

void RouterGridFieldTest::constructor_empty_notValid()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isValid());
}

