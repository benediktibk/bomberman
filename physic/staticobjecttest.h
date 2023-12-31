#ifndef PHYSIC_STATICOBJECTTEST_H
#define PHYSIC_STATICOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Physic
{
	class StaticObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(StaticObjectTest);
		 CPPUNIT_TEST(constructor_position5And4AndHeight1AndWidth2_positionIs5And4);
		 CPPUNIT_TEST(constructor_validSimulator_simulatorHasBodyCount1);
		 CPPUNIT_TEST(desturctor_empty_simulatorHasBodyCount0);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void constructor_position5And4AndHeight1AndWidth2_positionIs5And4();
		 void constructor_validSimulator_simulatorHasBodyCount1();
		 void desturctor_empty_simulatorHasBodyCount0();
	};
}

#endif
