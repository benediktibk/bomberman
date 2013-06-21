#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool CoveredByPlayerDecider::decide(const RouterGridField &field) const
{
	return field.isPlayer();
}
