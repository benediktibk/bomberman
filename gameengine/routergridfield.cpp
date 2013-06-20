#include "gameengine/routergridfield.h"
#include <assert.h>

using namespace GameEngine;

RouterGridField::RouterGridField()
{
	clear();
}

bool RouterGridField::isLooseWall() const
{
	return m_looseWall;
}

bool RouterGridField::isSolidWall() const
{
	return m_solidWall;
}

bool RouterGridField::isBomb() const
{
	return m_bomb;
}

bool RouterGridField::isPlayer() const
{
	return m_player;
}

bool RouterGridField::isDangerous() const
{
	return m_dangerous;
}

void RouterGridField::setLooseWall(bool value)
{
	assert(!m_player && !m_solidWall && !m_bomb);
	m_looseWall = value;
}

void RouterGridField::setSolidWall(bool value)
{
	assert(!m_player && !m_looseWall && !m_bomb);
	m_solidWall = value;
}

void RouterGridField::setBomb(bool value)
{
	assert(!m_looseWall && !m_solidWall);
	m_bomb = value;
	if (value)
		m_dangerous = true;
}

void RouterGridField::setPlayer(bool value)
{
	assert(!m_looseWall && !m_solidWall);
	m_player = value;
}

void RouterGridField::setDangerous(bool value)
{
	assert(!(m_bomb && !value));
	m_dangerous = value;
}

void RouterGridField::clear()
{
	m_looseWall = false;
	m_solidWall = false;
	m_bomb = false;
	m_player = false;
	m_dangerous = false;
}
