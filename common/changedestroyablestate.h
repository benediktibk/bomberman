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
    virtual ~ChangeDestroyableState();
    
    virtual void setChanged();
	virtual bool hasChanged();
	virtual void resetChanged();
    
    virtual bool isDestroyed() const;
	virtual void setDestroyed();
    
private:
    bool m_destroyed;
    bool m_changed;
    
};
}
#endif // CHANGEDESTROYABLESTATE_H
