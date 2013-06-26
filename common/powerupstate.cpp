#include "powerupstate.h"

using namespace Common;

PowerUpState::PowerUpState(UniqueIdCreator &creator, const Point &position, PowerUpType powerUpType):
    m_position(position),
    m_powerUpId(creator.getId()),
    m_creatorid(creator),
    m_width(1),
	m_height(1),
	m_powerUpType(powerUpType)
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

PowerUpType PowerUpState::getPowerUpType() const
{
	return m_powerUpType;
}

void PowerUpState::modifyPlayer(PlayerState& /*player*/) const
{ }

void PowerUpState::shouldBeDestroyed()
{
    setChanged();
}
