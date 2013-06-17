#include "leveldefinitionreadertest.h"
#include "leveldefinitionreader.h"

using namespace Common;

void LevelDefinitionReaderTest::readLevelFromLevelList_defaultLevel_resultIsDefaultLevel()
{
	LevelDefinitionReader levelReader;
	levelReader.readLevelFromLevelList("defaultlevel");
	struct LevelDefinitionReader::Level levelParameter;
	levelParameter = levelReader.getLevelParameters();

	CPPUNIT_ASSERT(levelParameter.name == "defaultlevel");
}
