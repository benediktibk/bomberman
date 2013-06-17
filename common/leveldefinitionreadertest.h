#ifndef COMMON_LEVELDEFINITIONREADERTEST_H
#define COMMON_LEVELDEFINITIONREADERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class LevelDefinitionReaderTest :
        public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(LevelDefinitionReaderTest);
	CPPUNIT_TEST(readLevelFromLevelList_defaultLevel_resultIsDefaultLevel);
    CPPUNIT_TEST_SUITE_END();

private:
	void readLevelFromLevelList_defaultLevel_resultIsDefaultLevel();

};
}

#endif // LEVELDEFINITIONREADERTEST_H
