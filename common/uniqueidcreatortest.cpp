#include "uniqueidcreatortest.h"
#include "uniqueidcreator.h"

using namespace Common;

void UniqueIdCreatorTest::getId_when_first()
{
	UniqueIdCreator id;

	unsigned int uniqueid = id.getId();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, uniqueid);
}

void UniqueIdCreatorTest::getId_when_third()
{
	UniqueIdCreator id;
	unsigned int uniqueid;

	uniqueid = id.getId();
	uniqueid = id.getId();
	uniqueid = id.getId();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, uniqueid);
}

void UniqueIdCreatorTest::getId_when_third_deleted()
{
	UniqueIdCreator id;
	unsigned int uniqueid;

	uniqueid = id.getId();
	uniqueid = id.getId();
	uniqueid = id.getId();
	id.removeId(uniqueid);
	uniqueid = id.getId();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, uniqueid);
}

void UniqueIdCreatorTest::getId_calledTwice_idCountIs2()
{
	UniqueIdCreator idCreator;

	idCreator.getId();
	idCreator.getId();

	CPPUNIT_ASSERT_EQUAL((size_t)2, idCreator.getIDCount());
}

void UniqueIdCreatorTest::removeID_calledTwiceAndThreeIDsFetched_idCountIs1()
{
	UniqueIdCreator idCreator;

	unsigned int firstID = idCreator.getId();
	unsigned int secondID = idCreator.getId();
	idCreator.getId();
	idCreator.removeId(firstID);
	idCreator.removeId(secondID);

	CPPUNIT_ASSERT_EQUAL((size_t)1, idCreator.getIDCount());
}
