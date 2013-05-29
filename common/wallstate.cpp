#include "wallstate.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator, WallState::WallType wallType, const Point &position) :
	m_position(position),
	m_wallid(creator.getId()),
	m_creatorid(creator),
	m_wallType(wallType)
{ }

WallState::~WallState()
{
	m_creatorid.removeId(m_wallid);
}

const Point &WallState::getPosition() const
{
	return m_position;
}

WallState::WallType WallState::getWallType() const
{
	return m_wallType;
}
