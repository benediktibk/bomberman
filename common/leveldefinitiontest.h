#ifndef LEVELDEFINITIONTEST_H
#define LEVELDEFINITIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{

class LevelDefinitionTest :
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(LevelDefinitionTest);
    CPPUNIT_TEST(getObjectTypeAtPosition_3And5_resultIsObjectTypeEmpty);
    CPPUNIT_TEST_SUITE_END();

private:
    void getObjectTypeAtPosition_3And5_resultIsObjectTypeEmpty();

};
}

#endif // LEVELDEFINITIONTEST_H
