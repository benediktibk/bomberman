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
	CPPUNIT_TEST_SUITE_END();

private:
	void getWidthOfFile_pareFileDefaultlevel_resultIs15();

};
}
#endif // CSVPARSERTEST_H
