#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool CoveredByLooseWallDecider::decide(const RouterGridField &field, const RouterGridField &, bool) const
{
	return field.isLooseWall();
}
