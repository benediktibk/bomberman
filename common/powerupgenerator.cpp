#include "powerupgenerator.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace Common;

PowerUpGenerator::PowerUpGenerator():
    m_randRange(100)
{ }

PowerUpType PowerUpGenerator::getTypeForRand(unsigned int rand)
{
    if (rand <= getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange)
        return PowerUpTypeMaxBomb;
    rand -= getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange;

    return PowerUpTypeNone;
}

double PowerUpGenerator::getPropabilityOfType(PowerUpType type)
{
    switch (type) {
    case PowerUpTypeMaxBomb:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

PowerUpType PowerUpGenerator::getRandomPowerUpType()
{
    unsigned int result;
    //srand(time(NULL));

    result = rand() % 10;

    if (result < 7)
        return PowerUpTypeNone;

    result = rand() % m_randRange;
    m_powerUpType = getTypeForRand(result);

    const PowerUpType randomPowerUpResult = m_powerUpType;
    return randomPowerUpResult;
}
