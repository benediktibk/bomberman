#include "powerupgenerator.h"
#include "randomdecision.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace Common;

PowerUpGenerator::PowerUpGenerator():
	m_powerUpPropability(0.25)
{ }

PowerUpType PowerUpGenerator::getRandomType()
{
	if (RandomDecision(1.0/3.0).decide())
		return PowerUpTypeMaxBombRange;

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
	RandomDecision decision(m_powerUpPropability);

	return decision.decide();
}
