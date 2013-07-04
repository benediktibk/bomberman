#include "gameengine/routergridfield.h"
#include <assert.h>

using namespace GameEngine;
using namespace Common;

RouterGridField::RouterGridField(const GridPoint &position) :
	m_position(position),
	m_valid(true)
{
	clear();
}

RouterGridField::RouterGridField() :
	m_valid(false)
{ }

bool RouterGridField::isLooseWall() const
{
	assert(m_valid);
	return m_looseWall;
}

bool RouterGridField::isSolidWall() const
{
	assert(m_valid);
	return m_solidWall;
}

bool RouterGridField::isBomb() const
{
	assert(m_valid);
	return m_bomb;
}

bool RouterGridField::isPlayer() const
{
	assert(m_valid);
	return m_player;
}

bool RouterGridField::isDangerous() const
{
	assert(m_valid);
	return m_dangerous;
}

bool RouterGridField::isFree() const
{
	assert(m_valid);
	return !isBomb() && !isPlayer() && !isLooseWall() && !isSolidWall();
}

bool RouterGridField::isPowerUp() const
{
	assert(m_valid);
	return m_powerUp;
}

void RouterGridField::setLooseWall(bool value)
{
	assert(m_valid);
	assert(!m_player && !m_solidWall && !m_bomb && !m_dangerous);
	m_looseWall = value;
}

void RouterGridField::setSolidWall(bool value)
{
	assert(m_valid);
	assert(!m_player && !m_looseWall && !m_bomb && !m_dangerous);
	m_solidWall = value;
}

void RouterGridField::setBomb(bool value)
{
	assert(m_valid);
	assert(!m_looseWall && !m_solidWall);
	m_bomb = value;
	if (value)
		m_dangerous = true;
}

void RouterGridField::setPlayer(bool value)
{
	assert(m_valid);
	m_player = value;
}

void RouterGridField::setDangerous(bool value)
{
	assert(m_valid);
	assert(!(m_bomb && !value));
	m_dangerous = value;
}

void RouterGridField::setPowerUp(bool value)
{
	assert(m_valid);
	assert((!m_looseWall && !m_solidWall) || !value);
	m_powerUp = value;
}

void RouterGridField::clear()
{
	m_looseWall = false;
	m_solidWall = false;
	m_bomb = false;
	m_player = false;
	m_dangerous = false;
	m_powerUp = false;
}

const GridPoint& RouterGridField::getPosition() const
{
	assert(m_valid);
	return m_position;
}

bool RouterGridField::isValid() const
{
	return m_valid;
}
