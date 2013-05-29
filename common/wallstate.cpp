#include "wallstate.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator, WallState::WallType wallType, const Point &position) :
	m_position(position),
	m_wallid(creator.getId()),
	m_creatorid(creator),
    m_wallType(wallType),
    m_width(1.0),
    m_height(1.0)
{ }

WallState::~WallState()
{
	m_creatorid.removeId(m_wallid);
}

const Point &WallState::getPosition() const
{
	return m_position;
}


unsigned int WallState::getWallId() const
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

double WallState::getWallHeight() const
{
    return m_height;
}

double WallState::getWallWidth() const
{
    return m_width;
}
