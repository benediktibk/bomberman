#include "powerupgenerator.h"
#include <stdlib.h>
#include <time.h>
#include "randomdecision.h"

using namespace std;
using namespace Common;

PowerUpGenerator::PowerUpGenerator():
	m_powerUpPropability(0.25)
{ }

PowerUpType PowerUpGenerator::getRandomType()
{
	if (RandomDecision(0.5).decide())
        return PowerUpTypeMaxBomb;

	return PowerUpTypeMaxVelocity;
}

PowerUpType PowerUpGenerator::getRandomPowerUpType()
{
    if (!createNewPowerup())
        return PowerUpTypeNone;

	return getRandomType();
}

bool PowerUpGenerator::createNewPowerup()
{
	RandomDecision decision(0.25);

	return decision.decide();
}
