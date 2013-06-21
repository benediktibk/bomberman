#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool NotDangerousAndFreeDecider::decide(const RouterGridField &field) const
{
	if (!field.isDangerous() && field.isFree())
		return true;
	else
		return false;
}
