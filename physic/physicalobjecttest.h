#ifndef PHYSIC_PHYSICALOBJECTTEST_H
#define PHYSIC_PHYSICALOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Physic
{
	class PhysicSimulator;

	class PhysicalObjectTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(PhysicalObjectTest);
		CPPUNIT_TEST(setCollisionGroup_5_collisionGroupIs5);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void setCollisionGroup_5_collisionGroupIs5();

	private:
		PhysicSimulator *m_simulator;
	};
}

#endif
