
#include "leveldefinitiontest.h"
#include "leveldefinition.h"

using namespace Common;

void LevelDefinitionTest::getObjectTypeAtPosition_3And5_resultIsObjectTypeEmpty()
{
	LevelDefinition level;

	CPPUNIT_ASSERT_EQUAL(LevelDefinition::ObjectTypeEmpty, level.getObjectTypeAtPosition(3,5));
}

void LevelDefinitionTest::getLevelHeight_resultIs50()
{
	LevelDefinition level;

	CPPUNIT_ASSERT_EQUAL((unsigned int)50, level.getLevelHeight());
}

void LevelDefinitionTest::getLevelWidth_resultIs50()
{
	LevelDefinition level;

	CPPUNIT_ASSERT_EQUAL((unsigned int)50, level.getLevelWidth());
}

void LevelDefinitionTest::setObjectTypeAtPosition_SolidWallAt3And5_resultIsObjectTypeSolidWall()
{
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall,3,5);

	CPPUNIT_ASSERT_EQUAL(LevelDefinition::ObjectTypeSolidWall, level.getObjectTypeAtPosition(3,5));
}

void LevelDefinitionTest::getPlayerStartPositionCount_twoPlayerStartPositions_2()
{
	LevelDefinition level(6, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 2);

	CPPUNIT_ASSERT_EQUAL((size_t)2, level.getPlayerStartPositionCount());
}

void LevelDefinitionTest::getObjectTypeAtPosition_buildLevelFromCSVFilePosition3And2_resultIsObjectTypeLooseWall()
{
	LevelDefinition level(CSVParser("testfiles/defaultlevel"));

	CPPUNIT_ASSERT_EQUAL(LevelDefinition::ObjectTypeLooseWall, level.getObjectTypeAtPosition(3,2));
}

void LevelDefinitionTest::isLevelBuildingCorrect_freeeeInsteadOfFreeInFile_isLevelBuildingIsFalse()
{
	LevelDefinition level(CSVParser("testfiles/defaultlevelerror2"));

	CPPUNIT_ASSERT(!level.isLevelBuildingCorrect());
}
