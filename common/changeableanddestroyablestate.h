#ifndef COMMON_CHANGEABLEANDDESTROYABLESTATE_H
#define COMMON_CHANGEABLEANDDESTROYABLESTATE_H

#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
class ChangeableAndDestroyableState :
        public ChangeableState,
        public DestroyableState
{
private:
	virtual void shouldBeDestroyed();
    
};
}
#endif // CHANGEDESTROYABLESTATE_H
