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
