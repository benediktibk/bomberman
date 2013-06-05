#include "common/playerstatetest.h"
#include "common/playerstate.h"
#include "common/uniqueidcreator.h"

using namespace Common;

void PlayerStateTest::setUp()
{
	m_idCreator = new UniqueIdCreator;
}

void PlayerStateTest::tearDown()
{
	delete m_idCreator;
}

void PlayerStateTest::constructor_idCreator_idFetched()
{
	PlayerState *player = new PlayerState(*m_idCreator);

	CPPUNIT_ASSERT_EQUAL((size_t)1, m_idCreator->getIDCount());
	delete player;
}

void PlayerStateTest::destructor_empty_idCountIsZero()
{
	PlayerState *player = new PlayerState(*m_idCreator);

	delete player;

	CPPUNIT_ASSERT_EQUAL((size_t)0, m_idCreator->getIDCount());
}


