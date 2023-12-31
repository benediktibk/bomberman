#ifndef PHYSIC_DYNAMICOBJECTTEST_H
#define PHYSIC_DYNAMICOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Physic
{
	class DynamicObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(DynamicObjectTest);
		 CPPUNIT_TEST(constructor_position5And4AndHeight1AndWidth2_positionIs5And4);
		 CPPUNIT_TEST(constructor_validSimulator_simulatorHasBodyCount1);
		 CPPUNIT_TEST(destructor_empty_simulatorHasBodyCount0);
		 CPPUNIT_TEST(applyLinearVelocity_5IntoXAndSimulationStepOf1_positionHasChanged5IntoX);
		 CPPUNIT_TEST(applyLinearVelocity_5IntoYAndSimulationStepOf01_positionHasChanged05IntoY);
		 CPPUNIT_TEST(constructor_position5And4AndHeight2AndWidth2_centerPositionIs6And5);
		 CPPUNIT_TEST(getVelocityX_velocityInXSetTo12_12);
		 CPPUNIT_TEST(getVelocityY_velocityInYSetTo5_5);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void constructor_position5And4AndHeight1AndWidth2_positionIs5And4();
		 void constructor_validSimulator_simulatorHasBodyCount1();
		 void destructor_empty_simulatorHasBodyCount0();
		 void applyLinearVelocity_5IntoXAndSimulationStepOf1_positionHasChanged5IntoX();
		 void applyLinearVelocity_5IntoYAndSimulationStepOf01_positionHasChanged05IntoY();
		 void constructor_position5And4AndHeight2AndWidth2_centerPositionIs6And5();
		 void getVelocityX_velocityInXSetTo12_12();
		 void getVelocityY_velocityInYSetTo5_5();
	};
}

#endif
