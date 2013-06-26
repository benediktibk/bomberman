#include "gameengine/routergridfieldtest.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

void RouterGridFieldTest::constructor_empty_isNotSolidWall()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isSolidWall());
}

void RouterGridFieldTest::constructor_empty_isNotLooseWall()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isLooseWall());
}

void RouterGridFieldTest::constructor_empty_isNotBomb()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isBomb());
}

void RouterGridFieldTest::constructor_empty_isNotPlayer()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isPlayer());
}

void RouterGridFieldTest::constructor_empty_isNotDangerous()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isDangerous());
}

void RouterGridFieldTest::constructor_empty_isNotPowerUp()
{
	RouterGridField field;

	CPPUNIT_ASSERT(!field.isPowerUp());
}

void RouterGridFieldTest::setSolidWall_true_isSolidWall()
{
	RouterGridField field;

	field.setSolidWall(true);

	CPPUNIT_ASSERT(field.isSolidWall());
}

void RouterGridFieldTest::setLooseWall_true_isLooseWall()
{
	RouterGridField field;

	field.setLooseWall(true);

	CPPUNIT_ASSERT(field.isLooseWall());
}

void RouterGridFieldTest::setBomb_true_isBomb()
{
	RouterGridField field;

	field.setBomb(true);

	CPPUNIT_ASSERT(field.isBomb());
}

void RouterGridFieldTest::setBomb_true_isDangerous()
{
	RouterGridField field;

	field.setBomb(true);

	CPPUNIT_ASSERT(field.isDangerous());
}

void RouterGridFieldTest::setPlayer_true_isPlayer()
{
	RouterGridField field;

	field.setPlayer(true);

	CPPUNIT_ASSERT(field.isPlayer());
}

void RouterGridFieldTest::setDangerous_true_isDangerous()
{
	RouterGridField field;

	field.setDangerous(true);

	CPPUNIT_ASSERT(field.isDangerous());
}

void RouterGridFieldTest::setPowerUp_true_isPowerUp()
{
	RouterGridField field;

	field.setPowerUp(true);

	CPPUNIT_ASSERT(field.isPowerUp());
}

void RouterGridFieldTest::isFree_nothingSet_true()
{
	RouterGridField field;

	CPPUNIT_ASSERT(field.isFree());
}

void RouterGridFieldTest::isFree_bombSet_false()
{
	RouterGridField field;

	field.setBomb(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_playerSet_false()
{
	RouterGridField field;

	field.setPlayer(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_looseWallSet_false()
{
	RouterGridField field;

	field.setLooseWall(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_solidWallSet_false()
{
	RouterGridField field;

	field.setSolidWall(true);

	CPPUNIT_ASSERT(!field.isFree());
}

void RouterGridFieldTest::isFree_dangerousSet_true()
{
	RouterGridField field;

	field.setDangerous(true);

	CPPUNIT_ASSERT(field.isFree());
}

void RouterGridFieldTest::isFree_powerUpSet_true()
{
	RouterGridField field;

	field.setPowerUp(true);

	CPPUNIT_ASSERT(field.isFree());
}

