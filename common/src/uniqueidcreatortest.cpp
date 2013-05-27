#include "uniqueidcreatortest.h".h"
#include "uniqueidcreator.h"
#include <sstream>

using namespace Common;


void UniqueIdCreatorTest::getId_when_first()
{
    UniqueIdCreator id;
    unsigned int uniqueid;
    uniqueid = id.getId();

    CPPUNIT_ASSERT_EQUAL(0, uniqueid);
}

void UniqueIdCreatorTest::getId_when_third()
{
    UniqueIdCreator id;
    unsigned int uniqueid;
        uniqueid = id.getId();
        uniqueid = id.getId();
        uniqueid = id.getId();
    CPPUNIT_ASSERT_EQUAL(2, uniqueid);
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
    CPPUNIT_ASSERT_EQUAL(2, uniqueid);
}
