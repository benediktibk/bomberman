#ifndef COMMON_POWERUPGENERATOR_H
#define COMMON_POWERUPGENERATOR_H

#include "powerupmaxbombstate.h"

namespace Common
{
class PowerUpGenerator
{
public:
    PowerUpGenerator();
    PowerUpType getRandomPowerUpType();

private:
	PowerUpType getRandomType();
    bool createNewPowerup();

private:
	const double m_powerUpPropability;
};
}

#endif
