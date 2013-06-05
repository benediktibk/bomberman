#include "wallstate.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator, WallState::WallType wallType, const Point &position) :
	m_position(position),
	m_wallId(creator.getId()),
	m_creatorId(creator),
	m_wallType(wallType),
	m_width(1),
	m_height(1)
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

double WallState::getHeight() const
{
	return m_height;
}

double WallState::getWidth() const
{
	return m_width;
}
