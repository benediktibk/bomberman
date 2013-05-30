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
