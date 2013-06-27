#include "wallstate.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator, WallState::WallType wallType, const Point &position) :
	m_position(position),
	m_wallId(creator.getId()),
	m_creatorId(creator),
	m_wallType(wallType),
	m_dimension(1)
{ }

WallState::~WallState()
{
	m_creatorId.removeId(m_wallId);
}

const Point &WallState::getPosition() const
{
	return m_position;
}

unsigned int WallState::getId() const
{
	return m_wallId;
}

void WallState::shouldBeDestroyed()
{
	setChanged();
}

WallState::WallType WallState::getWallType() const
{
	return m_wallType;
}

double WallState::getDimension() const
{
	return m_dimension;
}
