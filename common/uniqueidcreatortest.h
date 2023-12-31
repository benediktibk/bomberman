#ifndef COMMON_UNIQUEIDCREATORTEST_H
#define COMMON_UNIQUEIDCREATORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class UniqueIdCreatorTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(UniqueIdCreatorTest);
	 CPPUNIT_TEST(getId_when_third_deleted);
	 CPPUNIT_TEST(getId_when_third);
	 CPPUNIT_TEST(getId_when_first);
	 CPPUNIT_TEST(getId_calledTwice_idCountIs2);
	 CPPUNIT_TEST(removeID_calledTwiceAndThreeIDsFetched_idCountIs1);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void getId_when_third_deleted();
	 void getId_when_third();
	 void getId_when_first();
	 void getId_calledTwice_idCountIs2();
	 void removeID_calledTwiceAndThreeIDsFetched_idCountIs1();
};
}

#endif

