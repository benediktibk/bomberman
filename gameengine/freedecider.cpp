#include "gameengine/freedecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

bool FreeDecider::decide(const RouterGridField &field, const RouterGridField &, bool) const
{
	return field.isFree();
}
