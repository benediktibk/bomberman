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

void CSVParserTest::isFileCorrect_parseFileDefaultLevelError_resulIsFalse()
{
	CSVParser testRead;
	testRead.parseFile("defaultlevelerror");

	CPPUNIT_ASSERT(!testRead.isFileCorrect());
}

void CSVParserTest::couldOpenFile_parseFileWithNotExistingFileName_couldOpenFileIsFalse()
{
	CSVParser testRead;
	testRead.parseFile("default");

	CPPUNIT_ASSERT(!testRead.couldOpenFile());
}
