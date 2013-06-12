#include "common/playerstate.h"
#include "common/bombstate.h"
#include <assert.h>
#include <algorithm>

using namespace Common;
using namespace std;

PlayerState::PlayerState(UniqueIdCreator &creator) :
	m_direction(PlayerDirectionUp),
	m_placedBombCount(0),
	m_maxBombs(1),
	m_maximumSpeed(5.0),
	m_width(1),
	m_height(1),
	m_playerId(creator.getId()),
	m_creatorId(creator),
	m_moving(false)
{}

PlayerState::~PlayerState()
{
	m_creatorId.removeId(m_playerId);
}

unsigned int PlayerState::getId() const
{
	return m_playerId;
}

void PlayerState::setPosition(Point value)
{
	m_position = value;
}

Point PlayerState::getPosition() const
{
	return m_position;
}

void PlayerState::setDirectionUp()
{
	m_direction = PlayerDirectionUp;
}

void PlayerState::setDirectionDown()
{
	m_direction = PlayerDirectionDown;
}

void PlayerState::setDirectionLeft()
{
	m_direction = PlayerDirectionLeft;
}

void PlayerState::setDirectionRight()
{
	m_direction = PlayerDirectionRight;
}

PlayerState::PlayerDirection PlayerState::getDirection() const
{
	return m_direction;
}

void PlayerState::countBomb()
{
	m_placedBombCount += 1;
}

void PlayerState::reduceBombCount()
{
	m_placedBombCount -= 1;
}

unsigned int PlayerState::getBombCount()
{
	return m_placedBombCount;
}

double PlayerState::getMaximumSpeed() const
{
	return m_maximumSpeed;
}

double PlayerState::getSpeedIntoX() const
{
	if (!m_moving)
		return 0;

	double result = 0;
	switch(m_direction)
	{
	case PlayerState::PlayerDirectionDown:
	case PlayerState::PlayerDirectionUp:
		result = 0;
		break;
	case PlayerState::PlayerDirectionLeft:
		result = (-1)*getMaximumSpeed();
		break;
	case PlayerState::PlayerDirectionRight:
		result = getMaximumSpeed();
		break;
	}

	return result;
}

double PlayerState::getSpeedIntoY() const
{
	if (!m_moving)
		return 0;

	double result = 0;
	switch(m_direction)
	{
	case PlayerState::PlayerDirectionDown:
		result = (-1)*getMaximumSpeed();
		break;
	case PlayerState::PlayerDirectionUp:
		result = getMaximumSpeed();
		break;
	case PlayerState::PlayerDirectionLeft:
	case PlayerState::PlayerDirectionRight:
		result = 0;
		break;
	}

	return result;
}

void PlayerState::setMoving()
{
	m_moving = true;
}

void PlayerState::setNotMoving()
{
	m_moving = false;
}

bool PlayerState::isMoving() const
{
	return m_moving;
}

double PlayerState::getHeight() const
{
	return m_height;
}

void PlayerState::setWidth(double value)
{
	m_width = value;
}

void PlayerState::setHeight(double value)
{
	m_height = value;
}

double PlayerState::getWidth() const
{
	return m_width;
}

void PlayerState::setMaxBombs(unsigned int maxBombs)
{
	m_maxBombs = maxBombs;
}

void PlayerState::increaseMaxBombs()
{
	m_maxBombs += 1;
}

void PlayerState::increaseMaxBombs(unsigned int number)
{
	m_maxBombs += number;
}

unsigned int PlayerState::getMaxBombs() const
{
	return m_maxBombs;
}

unsigned int PlayerState::getRemainingBombs() const
{
	assert(m_maxBombs >= m_placedBombCount);
	return m_maxBombs - m_placedBombCount;
}

bool PlayerState::canPlayerPlaceBomb() const
{
	if(getRemainingBombs() == 0)
		return false;
	else
		return true;
}

Point PlayerState::getCenterPosition() const
{
	return m_position + Point(m_width/2,m_height/2);
}

void PlayerState::doNotCollideWith(const BombState *bomb)
{
	m_bombsNotToCollideWith.push_back(bomb);
}

vector<const BombState *> PlayerState::getBombsNotToCollideWith() const
{
	return m_bombsNotToCollideWith;
}

void PlayerState::removeBombFromDoNotCollideList(const BombState *bomb)
{
	vector<const BombState *>::iterator end = remove(m_bombsNotToCollideWith.begin(), m_bombsNotToCollideWith.end(), bomb);
	m_bombsNotToCollideWith.erase(end, m_bombsNotToCollideWith.end());
}

void PlayerState::increaseMaximumSpeed()
{
    m_maximumSpeed += 2;
}
