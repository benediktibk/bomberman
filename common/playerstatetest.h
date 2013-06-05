#ifndef COMMON_PLAYERSTATETEST_H
#define COMMON_PLAYERSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;

	class PlayerStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(PlayerStateTest);
		CPPUNIT_TEST(constructor_idCreator_idFetched);
		CPPUNIT_TEST(destructor_empty_idCountIsZero);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_idCreator_idFetched();
		void destructor_empty_idCountIsZero();

	private:
		UniqueIdCreator *m_idCreator;
	};
}

#endif
