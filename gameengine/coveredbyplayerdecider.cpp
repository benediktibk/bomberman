#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/routergridfield.h"
#include "gameengine/router.h"

using namespace GameEngine;

CoveredByPlayerDecider::CoveredByPlayerDecider(const Router &router, unsigned int bombRange, bool considerEscape) :
	m_router(router),
	m_bombRange(bombRange),
	m_considerEscape(considerEscape)
{ }

bool CoveredByPlayerDecider::decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const
{
	if (m_considerEscape)
	{
		if (!previousFieldValid)
			return false;

		if (!field.isPlayer())
			return false;

		return m_router.canEscapeFromIfBombPlaced(previousField.getPosition(), m_bombRange);
	}
	else
		return field.isPlayer();
}
