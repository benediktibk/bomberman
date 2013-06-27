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
	 CPPUNIT_TEST(constructor_dimensionSetTo1_dimensionIs1);
	 CPPUNIT_TEST(getPhysicalHeight_notMovingAndDimension1_1);
	 CPPUNIT_TEST(getPhysicalWidth_notMovingAndDimension1_1);
	 CPPUNIT_TEST(getPhysicalHeight_movingIntoXAndDimension1_05);
	 CPPUNIT_TEST(getPhysicalHeight_movingIntoYAndDimension1_1);
	 CPPUNIT_TEST(getPhysicalWidth_movingIntoXAndDimension1_1);
	 CPPUNIT_TEST(getPhysicalWidth_movingIntoYAndDimension1_05);
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
	 void constructor_dimensionSetTo1_dimensionIs1();
	 void getPhysicalHeight_notMovingAndDimension1_1();
	 void getPhysicalWidth_notMovingAndDimension1_1();
	 void getPhysicalHeight_movingIntoXAndDimension1_05();
	 void getPhysicalHeight_movingIntoYAndDimension1_1();
	 void getPhysicalWidth_movingIntoXAndDimension1_1();
	 void getPhysicalWidth_movingIntoYAndDimension1_05();
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
