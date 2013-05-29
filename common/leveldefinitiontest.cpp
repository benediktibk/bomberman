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
