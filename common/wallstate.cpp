#include "wallstate.h"

using namespace Common;

WallState::WallState(UniqueIdCreator &creator) :
        m_wallid(creator.getId()),
        m_creatorid(creator)
{
}

WallState::~WallState()
{
    m_creatorid.removeId(m_wallid);
}

void WallState::setPosition(const Point &value)
{
    m_position = value;
}

const Point &WallState::getPosition() const
{
    return m_position;
}
