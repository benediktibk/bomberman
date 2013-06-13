#include "powerupgenerator.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace Common;

PowerUpGenerator::PowerUpGenerator():
    m_randRange(100),
    m_powerUpPropability(4)
{ }

PowerUpType PowerUpGenerator::getTypeForRand(unsigned int rand)
{
    if (rand < getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange)
        return PowerUpTypeMaxBomb;
    rand -= getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange;

    if (rand < getPropabilityOfType(PowerUpTypeMaxVelocity)*m_randRange)
        return PowerUpTypeMaxVelocity;
    rand -= getPropabilityOfType(PowerUpTypeMaxVelocity)*m_randRange;

    return PowerUpTypeNone;
}

double PowerUpGenerator::getPropabilityOfType(PowerUpType type)
{
    switch (type) {
    case PowerUpTypeMaxBomb:
        return 0.5;
        break;
    case PowerUpTypeMaxVelocity:
        return 0.5;
        break;
    default:
        return 0;
        break;
    }
}

PowerUpType PowerUpGenerator::getRandomPowerUpType()
{
    if (!createNewPowerup())
        return PowerUpTypeNone;

    m_powerUpType = getTypeForRand(rand() % m_randRange);

    const PowerUpType randomPowerUpResult = m_powerUpType;
    return randomPowerUpResult;
}

bool PowerUpGenerator::createNewPowerup()
{

    if ( (rand() % m_powerUpPropability) == 0)
        return true;
    return false;

}
