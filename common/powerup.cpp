#include "powerup.h"

using namespace Common;

PowerUp::PowerUp(UniqueIdCreator &creator, const Point &position):
    m_position(position),
    m_powerUpId(creator.getId()),
    m_creatorid(creator),
    m_width(1),
    m_height(1)
{ }

PowerUp::~PowerUp()
{
    m_creatorid.removeId(m_powerUpId);
}

const Point& PowerUp::getPosition() const
{
    return m_position;
}

unsigned int PowerUp::getId() const
{
    return m_powerUpId;
}

double PowerUp::getWidth() const
{
    return m_width;
}

double PowerUp::getHeight() const
{
    return m_height;
}
