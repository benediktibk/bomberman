#include "csvparsertest.h"
#include "csvparser.h"

using namespace Common;

void CSVParserTest::getWidthOfFile_pareFileDefaultlevel_resultIs15()
{
	CSVParser testRead;
	testRead.parseFile("defaultlevel");

	CPPUNIT_ASSERT_EQUAL((unsigned int)15, testRead.getWidthOfFile());
}

void CSVParserTest::getHeightOfFile_pareFileDefaultlevel_resultIs10()
{
	CSVParser testRead;
	testRead.parseFile("defaultlevel");

	CPPUNIT_ASSERT_EQUAL((unsigned int)10, testRead.getHeightOfFile());
}

void CSVParserTest::getTextInField_position3And2_resultIsLoose()
{
	CSVParser testRead;
	testRead.parseFile("defaultlevel");

	CPPUNIT_ASSERT_EQUAL((std::string)"loose", testRead.getTextInField(3,2));
}
