#include "powerupgenerator.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace Common;

PowerUpGenerator::PowerUpGenerator():
    m_randRange(100)
{
/*
    unsigned int result;
    srand(time(NULL));

    result = rand() % m_randRange;
    getTypeForRand(result);
*/
}

PowerUpGenerator::PowerUpType PowerUpGenerator::getTypeForRand(unsigned int rand)
{
    if (rand < getPropabilityOfType(PowerUpTypeBombPackage)*m_randRange)
        return PowerUpTypeBombPackage;
    rand -= getPropabilityOfType(PowerUpTypeBombPackage)*m_randRange;

    if (rand < getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange)
        return PowerUpTypeMaxBomb;
    rand -= getPropabilityOfType(PowerUpTypeMaxBomb)*m_randRange;

    return PowerUpTypeBombPackage;
}

double PowerUpGenerator::getPropabilityOfType(PowerUpGenerator::PowerUpType type)
{
    switch (type) {
    case PowerUpTypeBombPackage:
        return 0.5;
        break;
    case PowerUpTypeMaxBomb:
        return 0.5;
        break;
    default:
        return 0;
        break;
    }
}
