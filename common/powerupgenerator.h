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
    double getPropabilityOfType(PowerUpType type);
    PowerUpType getTypeForRand(unsigned int rand);
    bool createNewPowerup();

private:
    unsigned int m_randRange;
    unsigned int m_powerUpPropability;
    PowerUpType m_powerUpType;
};
}

#endif
