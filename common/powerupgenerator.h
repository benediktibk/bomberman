#ifndef COMMON_POWERUPGENERATOR_H
#define COMMON_POWERUPGENERATOR_H

#include "powerupmaxbombstate.h"

namespace Common
{
class PowerUpGenerator
{
public:
    enum PowerUpType
    {
        PowerUpTypeNone,
        PowerUpTypeMaxBomb
    };

    PowerUpGenerator();
    PowerUpType getRandomPowerUpType();

private:
    double getPropabilityOfType(PowerUpType type);
    PowerUpType getTypeForRand(unsigned int rand);

private:
    unsigned int m_randRange;
    PowerUpType m_powerUpType;
};
}

#endif
