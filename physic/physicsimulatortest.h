#ifndef PHYSIC_PHYSICSIMULATORTEST_H
#define PHYSIC_PHYSICSIMULATORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Physic
{
class PhysicSimulatorTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(PhysicSimulatorTest);
	 CPPUNIT_TEST(simulateStep_timeBelowMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect);
	 CPPUNIT_TEST(simulateStep_timeAboveMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void simulateStep_timeBelowMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect();
	 void simulateStep_timeAboveMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect();
};
}

#endif
