#include "csvparsertest.h"
#include "csvparser.h"

using namespace Common;

void CSVParserTest::getWidthOfFile_pareFileDefaultlevel_resultIs15()
{
	CSVParser testRead;
	testRead.parseFile("defaultlevel");

	CPPUNIT_ASSERT_EQUAL((unsigned int)15, testRead.getWidthOfFile());
}
