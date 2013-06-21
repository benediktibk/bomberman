#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool CoveredByLooseWallDecider::decide(const RouterGridField &field) const
{
	return field.isLooseWall();
}
