#ifndef GAMEENGINE_COVEREDBYPOWERUPDECIDERTEST_H
#define GAMEENGINE_COVEREDBYPOWERUPDECIDERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
class CoveredByPowerUpDeciderTest :
		public CPPUNIT_NS::TestFixture

{
	CPPUNIT_TEST_SUITE(CoveredByPowerUpDeciderTest);
	CPPUNIT_TEST(decide_defaultField_false);
	CPPUNIT_TEST(decide_playerAtField_true);
	CPPUNIT_TEST_SUITE_END();

private:
	void decide_defaultField_false();
	void decide_playerAtField_true();

};
}
#endif
