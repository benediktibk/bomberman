#include "enemystatetest.h"
#include "enemystate.h"

using namespace Common;

void EnemyStateTest::setPosition_5And4_positionIs5And4()
{
	EnemyState enemy;

	enemy.setPosition(Point(5, 4));

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), enemy.getPosition());
}