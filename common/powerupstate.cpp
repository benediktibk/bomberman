#include "powerupstate.h"

using namespace Common;

PowerUpState::PowerUpState(UniqueIdCreator &creator, const Point &position):
    m_position(position),
    m_powerUpId(creator.getId()),
    m_creatorid(creator),
    m_width(1),
    m_height(1)
{ }

PowerUpState::~PowerUpState()
{
    m_creatorid.removeId(m_powerUpId);
}

const Point& PowerUpState::getPosition() const
{
    return m_position;
}

unsigned int PowerUpState::getId() const
{
    return m_powerUpId;
}

double PowerUpState::getWidth() const
{
    return m_width;
}

double PowerUpState::getHeight() const
{
    return m_height;
}

void PowerUpState::modifyPlayer(PlayerState& /*player*/)
{ }
