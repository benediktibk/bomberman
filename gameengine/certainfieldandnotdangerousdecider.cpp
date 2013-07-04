#include "gameengine/certainfieldandnotdangerousdecider.h"
#include "gameengine/routergridfield.h"
#include <algorithm>

using namespace GameEngine;
using namespace Common;
using namespace std;

CertainFieldAndNotDangerousDecider::CertainFieldAndNotDangerousDecider(const vector<GridPoint> &possibleTargets) :
	m_possibleTargets(possibleTargets)
{ }

bool CertainFieldAndNotDangerousDecider::decide(const RouterGridField &field, const RouterGridField &, bool) const
{
	if (	count(m_possibleTargets.begin(), m_possibleTargets.end(), field.getPosition()) == 1 &&
			!field.isDangerous() &&
			field.isFree())
		return true;
	else
		return false;
}
