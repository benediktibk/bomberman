#include "wallstate.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator, WallState::WallType wallType, const Point &position) :
	m_position(position),
	m_wallid(creator.getId()),
	m_creatorid(creator),
	m_wallType(wallType),
	m_width(1),
	m_height(1)
{ }

WallState::~WallState()
{
	m_creatorid.removeId(m_wallid);
}

const Point &WallState::getPosition() const
{
	return m_position;
}

WallState::WallState(const WallState &wall) :
    m_position(wall.getPosition()),
    m_wallid(0),
    m_creatorid(wall.m_creatorid),
    m_wallType(wall.getWallType())
{}

unsigned int WallState::getId() const
{
	return m_wallid;
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
