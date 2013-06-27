#include "bombstate.h"
#include <assert.h>

using namespace Common;

BombState::BombState(UniqueIdCreator &creator, unsigned int playerID, const Point &position, unsigned int destructionRange) :
	m_playerID(playerID),
	m_position(position),
	m_lifeTime(initialLifeTime()),
	m_dimension(1),
	m_destructionRange(destructionRange),
	m_bombId(creator.getId()),
	m_creatorId(creator)
{
	assert(m_destructionRange > 0);
}

BombState::~BombState()
{
	m_creatorId.removeId(m_bombId);
}

const Point &BombState::getPosition() const
{
	return m_position;
}

void BombState::setLifeTime(double time)
{
	m_lifeTime = time;
	setChanged();
}

double BombState::getLifeTime() const
{
	return m_lifeTime;
}

unsigned int BombState::getDestructionRange() const
{
	return m_destructionRange;
}

unsigned int BombState::getID() const
{
	return m_bombId;
}

unsigned int BombState::getPlayerID() const
{
	return m_playerID;
}

double BombState::initialLifeTime()
{
	return 3;
}

double BombState::getDimension() const
{
	return m_dimension;
}

void BombState::shouldBeDestroyed()
{
	setChanged();
}
