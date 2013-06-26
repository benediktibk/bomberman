#ifndef GAMEENGINE_COVEREDBYPOWERUPDECIDER_H
#define GAMEENGINE_COVEREDBYPOWERUPDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
class CoveredByPowerUpDecider :
		public RouterGridFieldDecider
{
public:
	virtual bool decide(const RouterGridField &field) const;
};
}

#endif
