#ifndef GAMEENGINE_COVEREDBYPOWERUP_H
#define GAMEENGINE_COVEREDBYPOWERUP_H

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
