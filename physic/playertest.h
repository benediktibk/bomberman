#ifndef PHYSIC_PLAYERTEST_H
#define PHYSIC_PLAYERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;
	class PlayerState;
}

namespace Physic
{
class PlayerTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(PlayerTest);
	 CPPUNIT_TEST(constructor_validDimensions_bodyCountOfSimulatorIs1);
	 CPPUNIT_TEST(destructor_empty_bodyCountOfSimulatorIs0);
	 CPPUNIT_TEST(getPosition_positionSetTo2And3_2And3);
	 CPPUNIT_TEST(getCenterPosition_positionSetTo2And3WithHeightAndWidth2_3And4);
	 CPPUNIT_TEST(constructor_heightSetTo2_heightIs2);
	 CPPUNIT_TEST(constructor_widthSetTo4_widthIs4);
	 CPPUNIT_TEST(getPhysicalHeight_notMovingAndHeight4_4);
	 CPPUNIT_TEST(getPhysicalWidth_notMovingAndWidth2_2);
	 CPPUNIT_TEST(getPhysicalHeight_movingIntoXAndHeight4_2);
	 CPPUNIT_TEST(getPhysicalHeight_movingIntoYAndHeight4_4);
	 CPPUNIT_TEST(getPhysicalWidth_movingIntoXAndWidth6_6);
	 CPPUNIT_TEST(getPhysicalWidth_movingIntoYAndWith6_3);
	 CPPUNIT_TEST(applyLinearVelocity_4And0_velocityXIs4);
	 CPPUNIT_TEST(applyLinearVelocity_0And5_velocityYIs5);
	 CPPUNIT_TEST(getPosition_movingIntoX_correctPosition);
	 CPPUNIT_TEST(getPosition_movingIntoY_correctPosition);
	 CPPUNIT_TEST(getCenterPosition_movingIntoX_correctPosition);
	 CPPUNIT_TEST(getCenterPosition_movingIntoY_correctPosition);
	 CPPUNIT_TEST(getVelocityX_notMoving_0);
	 CPPUNIT_TEST(getVelocityY_notMoving_0);
     CPPUNIT_TEST(getCenterPosition_movingIntoYIntoOtherPlayer_correctPosition);
	 CPPUNIT_TEST_SUITE_END();

public:
	 virtual void setUp();
	 virtual void tearDown();

private:
	 void constructor_validDimensions_bodyCountOfSimulatorIs1();
	 void destructor_empty_bodyCountOfSimulatorIs0();
	 void getPosition_positionSetTo2And3_2And3();
	 void getCenterPosition_positionSetTo2And3WithHeightAndWidth2_3And4();
	 void constructor_heightSetTo2_heightIs2();
	 void constructor_widthSetTo4_widthIs4();
	 void getPhysicalHeight_notMovingAndHeight4_4();
	 void getPhysicalWidth_notMovingAndWidth2_2();
	 void getPhysicalHeight_movingIntoXAndHeight4_2();
	 void getPhysicalHeight_movingIntoYAndHeight4_4();
	 void getPhysicalWidth_movingIntoXAndWidth6_6();
	 void getPhysicalWidth_movingIntoYAndWith6_3();
	 void applyLinearVelocity_4And0_velocityXIs4();
	 void applyLinearVelocity_0And5_velocityYIs5();
	 void getPosition_movingIntoX_correctPosition();
	 void getPosition_movingIntoY_correctPosition();
	 void getCenterPosition_movingIntoX_correctPosition();
	 void getCenterPosition_movingIntoY_correctPosition();
	 void getVelocityX_notMoving_0();
	 void getVelocityY_notMoving_0();
     void getCenterPosition_movingIntoYIntoOtherPlayer_correctPosition();

private:
	 Common::UniqueIdCreator *m_playerIDCreator;
	 Common::PlayerState *m_playerOneState;
     Common::PlayerState *m_playerTwoState;
};
}

#endif
