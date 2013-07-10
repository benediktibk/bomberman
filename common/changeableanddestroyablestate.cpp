#include "common/changeableanddestroyablestate.h"

using namespace Common;

void ChangeableAndDestroyableState::shouldBeDestroyed()
{
	setChanged();
}
