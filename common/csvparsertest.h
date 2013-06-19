#ifndef COMMON_CSVPARSERTEST_H
#define COMMON_CSVPARSERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{

class CSVParserTest :
	public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CSVParserTest);
	CPPUNIT_TEST(getWidthOfFile_pareFileDefaultlevel_resultIs15);
	CPPUNIT_TEST(getHeightOfFile_pareFileDefaultlevel_resultIs10);
	CPPUNIT_TEST(getTextInField_position3And2_resultIsLoose);
	CPPUNIT_TEST(isFileCorrect_parseFileDefaultLevelError_resulIsFalse);
	CPPUNIT_TEST(couldOpenFile_parseFileWithNotExistingFileName_couldOpenFileIsFalse);
	CPPUNIT_TEST_SUITE_END();

private:
	void getWidthOfFile_pareFileDefaultlevel_resultIs15();
	void getHeightOfFile_pareFileDefaultlevel_resultIs10();
	void getTextInField_position3And2_resultIsLoose();
	void isFileCorrect_parseFileDefaultLevelError_resulIsFalse();
	void couldOpenFile_parseFileWithNotExistingFileName_couldOpenFileIsFalse();

};
}
#endif // CSVPARSERTEST_H
