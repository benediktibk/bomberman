#include "gameengine/coveredbypowerupdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool CoveredByPowerUpDecider::decide(const RouterGridField &field) const
{
	return field.isPowerUp() && !field.isDangerous();
}
