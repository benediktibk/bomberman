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
		 CPPUNIT_TEST(simulateStep_collisionOfDynamicWithStaticObject_dynamicObjectPositionIsCorrect);
		 CPPUNIT_TEST(simulateStep_collisionOfDynamicWithStaticObject_staticObjectPositionIsNotChanged);
		 CPPUNIT_TEST(simulateStep_collisionOfDynamicWithDynamicObject_firstDynamicObjectPositionIsCorrect);
		 CPPUNIT_TEST(simulateStep_collisionOfDynamicWithDynamicObject_secondDynamicObjectPositionIsCorrect);
		 CPPUNIT_TEST(simulateStep_dynamicObjectInSameNegativeCollisionGroupAsStaticObject_doNotCollide);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void simulateStep_timeBelowMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect();
		 void simulateStep_timeAboveMaximumStepTimeAndLinearMovingObject_objectPositionIsCorrect();
		 void simulateStep_collisionOfDynamicWithStaticObject_dynamicObjectPositionIsCorrect();
		 void simulateStep_collisionOfDynamicWithStaticObject_staticObjectPositionIsNotChanged();
		 void simulateStep_collisionOfDynamicWithDynamicObject_firstDynamicObjectPositionIsCorrect();
		 void simulateStep_collisionOfDynamicWithDynamicObject_secondDynamicObjectPositionIsCorrect();
		 void simulateStep_dynamicObjectInSameNegativeCollisionGroupAsStaticObject_doNotCollide();
	};
}

#endif
