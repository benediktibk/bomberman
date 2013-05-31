#ifndef COMMON_POWERUPGENERATOR_H
#define COMMON_POWERUPGENERATOR_H

#include "powerupbombpackstate.h"
#include "powerupmaxbombstate.h"

namespace Common
{
class PowerUpGenerator
{
public:
    enum PowerUpType
    {
        PowerUpTypeMaxBomb,
        PowerUpTypeBombPackage
    };

    PowerUpGenerator();

private:
    double getPropabilityOfType(PowerUpType type);
    PowerUpType getTypeForRand(unsigned int rand);

private:
    unsigned int m_randRange;
};
}

#endif
