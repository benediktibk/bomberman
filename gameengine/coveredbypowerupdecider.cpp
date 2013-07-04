#include "gameengine/coveredbypowerupdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool CoveredByPowerUpDecider::decide(const RouterGridField &field, const RouterGridField &, bool) const
{
	return field.isPowerUp() && !field.isDangerous();
}
