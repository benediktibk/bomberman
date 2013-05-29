#include "wallstate.h"
//#include "physic/staticobject.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator, WallState::WallType wallType) :
		m_wallid(creator.getId()),
		m_creatorid(creator),
		m_wallType(wallType)
{ }

WallState::~WallState()
{
	m_creatorid.removeId(m_wallid);
}

void WallState::setPosition(const Point &value)
{
	m_position = value;
	setChanged();
}

const Point &WallState::getPosition() const
{
	return m_position;
}


unsigned int WallState::getWallId() const
{
    return m_wallid;
}

WallState::WallType WallState::getWallType() const
{
    return m_wallType;
 }
