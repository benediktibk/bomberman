#include "gameengine/certainfieldandnotdangerousdecidertest.h"
#include "gameengine/certainfieldandnotdangerousdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;
using namespace Common;
using namespace std;

void CertainFieldAndNotDangerousDeciderTest::decide_notDangerousFieldWhichIsNotATarget_false()
{
	CertainFieldAndNotDangerousDecider decider(m_targets);
	RouterGridField field(GridPoint(1, 2));

	CPPUNIT_ASSERT(!decider.decide(field, field, false));
}

void CertainFieldAndNotDangerousDeciderTest::decide_dangerousFieldWhichIsATarget_false()
{
	CertainFieldAndNotDangerousDecider decider(m_targets);
	RouterGridField field(GridPoint(3, 0));
	field.setDangerous(true);

	CPPUNIT_ASSERT(!decider.decide(field, field, false));
}

void CertainFieldAndNotDangerousDeciderTest::decide_notDangerousFieldWhichIsATarget_true()
{
	CertainFieldAndNotDangerousDecider decider(m_targets);
	RouterGridField field(GridPoint(3, 0));

	CPPUNIT_ASSERT(decider.decide(field, field, false));
}

void CertainFieldAndNotDangerousDeciderTest::setUp()
{
	m_targets.clear();
	m_targets.push_back(GridPoint(5, 6));
	m_targets.push_back(GridPoint(3, 0));
}
