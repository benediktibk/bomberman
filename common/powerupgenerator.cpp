#include "powerupgenerator.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace Common;

PowerUpGenerator::PowerUpGenerator():
    m_randRange(100)
{ }

PowerUpGenerator::PowerUpType PowerUpGenerator::getTypeForRand(unsigned int rand)
{
    if (rand < getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange)
        return PowerUpTypeMaxBomb;
    rand -= getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange;

    return PowerUpTypeNone;
}

double PowerUpGenerator::getPropabilityOfType(PowerUpGenerator::PowerUpType type)
{
    switch (type) {
    case PowerUpTypeNone:
        return 0.8;
        break;
    case PowerUpTypeMaxBomb:
        return 0.2;
        break;
    default:
        return 0;
        break;
    }
}

PowerUpGenerator::PowerUpType PowerUpGenerator::getRandomPowerUpType()
{
    unsigned int result;
    srand(time(NULL));

    result = rand() % m_randRange;
    m_powerUpType = getTypeForRand(result);

    const PowerUpType randomPowerUpResult = m_powerUpType;
    return randomPowerUpResult;
}
