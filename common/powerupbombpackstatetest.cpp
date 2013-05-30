#include "powerupbombpackstatetest.h"
#include "powerupbombpackstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void PowerUpBombPackStateTest::getPowerUpWidth_widthIs1()
{
    UniqueIdCreator id;
    PowerUpBombPackState bombPackage(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, bombPackage.getWidth());
}

void PowerUpBombPackStateTest::getPowerUpHeight_heightIs1()
{
    UniqueIdCreator id;
    PowerUpBombPackState bombPackage(id, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, bombPackage.getHeight());
}
