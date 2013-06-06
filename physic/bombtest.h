#ifndef PHYSIC_BOMBTEST_H
#define PHYSIC_BOMBTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "common/uniqueidcreator.h"

namespace Physic
{
	class BombTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE(BombTest);
		CPPUNIT_TEST(doNotCollideWith_player_playerDoesntCollide);
		CPPUNIT_TEST_SUITE_END();

	private:
		void doNotCollideWith_player_playerDoesntCollide();

	private:
		Common::UniqueIdCreator m_bombIDCreator;
		Common::UniqueIdCreator m_playerIDCreator;
	};
}

#endif
