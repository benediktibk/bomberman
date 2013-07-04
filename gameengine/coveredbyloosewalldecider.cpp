#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/routergridfield.h"
#include "gameengine/router.h"

using namespace GameEngine;

CoveredByLooseWallDecider::CoveredByLooseWallDecider(const Router &router, unsigned int bombRange, bool considerEscape) :
	m_router(router),
	m_bombRange(bombRange),
	m_considerEscape(considerEscape)
{ }

bool CoveredByLooseWallDecider::decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const
{
	if (m_considerEscape)
	{
		if (!previousFieldValid)
			return false;

		if (!field.isLooseWall())
			return false;

		return m_router.canEscapeFromIfBombPlaced(previousField.getPosition(), m_bombRange);
	}
	else
		return field.isLooseWall();
}
