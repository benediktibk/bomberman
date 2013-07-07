#ifndef COMMON_CHANGEDESTROYABLESTATE_H
#define COMMON_CHANGEDESTROYABLESTATE_H

#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
class ChangeDestroyableState :
        public ChangeableState,
        public DestroyableState
{
public:
    ChangeDestroyableState();
    
    void setChangeAndDestroyed();
    // wenn zerstört dann auch change
    
private:
    bool m_destroyed;
    bool m_changed;
    
};
}
#endif // CHANGEDESTROYABLESTATE_H
