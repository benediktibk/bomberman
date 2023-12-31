#ifndef COMMON_LEVELDEFINITIONTEST_H
#define COMMON_LEVELDEFINITIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class LevelDefinitionTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LevelDefinitionTest);
		CPPUNIT_TEST(getObjectTypeAtPosition_3And5_resultIsObjectTypeEmpty);
		CPPUNIT_TEST(getLevelHeight_resultIs50);
		CPPUNIT_TEST(getLevelWidth_resultIs50);
		CPPUNIT_TEST(setObjectTypeAtPosition_SolidWallAt3And5_resultIsObjectTypeSolidWall);
		CPPUNIT_TEST(getPlayerStartPositionCount_twoPlayerStartPositions_2);
		CPPUNIT_TEST(getObjectTypeAtPosition_buildLevelFromCSVFilePosition3And2_resultIsObjectTypeLooseWall);
		CPPUNIT_TEST(isLevelBuildingCorrect_freeeeInsteadOfFreeInFile_isLevelBuildingIsFalse);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getObjectTypeAtPosition_3And5_resultIsObjectTypeEmpty();
		void getLevelHeight_resultIs50();
		void getLevelWidth_resultIs50();
		void setObjectTypeAtPosition_SolidWallAt3And5_resultIsObjectTypeSolidWall();
		void getPlayerStartPositionCount_twoPlayerStartPositions_2();
		void getObjectTypeAtPosition_buildLevelFromCSVFilePosition3And2_resultIsObjectTypeLooseWall();
		void isLevelBuildingCorrect_freeeeInsteadOfFreeInFile_isLevelBuildingIsFalse();
	};
}

#endif
