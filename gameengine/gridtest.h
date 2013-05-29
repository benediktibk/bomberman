#ifndef GAMEENGINE_GRIDTEST_H
#define GAMEENGINE_GRIDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
class GridTest :
        public CPPUNIT_NS::TestFixture
{
     CPPUNIT_TEST_SUITE(GridTest);
     CPPUNIT_TEST(isPlaceEmpty_TestOnEmptyVector_true);
     CPPUNIT_TEST(isPlaceEmpty_TestNotEmptyVector_false);
     CPPUNIT_TEST(addBombAtPlace_add_at3_3);
     CPPUNIT_TEST_SUITE_END();

private:
     void isPlaceEmpty_TestOnEmptyVector_true();
     void isPlaceEmpty_TestNotEmptyVector_false();
     void removeWall_from_3_3();
     void removeBomb_from_3_3();
     void addWallAtPlace_add_at3_3();
     void addBombAtPlace_add_at3_3();
};
}

#endif

