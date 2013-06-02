#include "player.h"
#include "dynamicobject.h"
#include <assert.h>

using namespace Common;
using namespace Physic;


Player::Player(PhysicSimulator &simulator, const Point &position, double width, double height) :
	m_simulator(simulator),
	m_object(0),
	m_width(width),
	m_height(height),
	m_physicalWidth(width),
	m_physicalHeight(height)
{
	updateObjectToPhysicalDimensions(position);
}

Player::~Player()
{
	delete m_object;
}

Point Player::getPosition() const
{
	assert(m_object != 0);
	return m_object->getPosition();
}

Point Player::getCenterPosition() const
{
	assert(m_object != 0);
	return m_object->getCenterPosition();
}

void Player::applyLinearVelocity(double velocityIntoX, double velocityIntoY)
{
	assert(velocityIntoX == 0 || velocityIntoY == 0);

	if (velocityIntoX != 0)
	{
		m_physicalWidth = m_width;
		m_physicalHeight = m_height/2;
	}

	if (velocityIntoY != 0)
	{
		m_physicalWidth = m_width/2;
		m_physicalHeight = m_height;
	}

	updateObjectToPhysicalDimensions(m_object->getPosition());
	m_object->applyLinearVelocity(velocityIntoX, velocityIntoY);
}

double Player::getVelocityX() const
{
	assert(m_object != 0);
	return m_object->getVelocityX();
}

double Player::getVelocityY() const
{
	assert(m_object != 0);
	return m_object->getVelocityY();
}

double Player::getWidth() const
{
	return m_width;
}

double Player::getHeight() const
{
	return m_height;
}

double Player::getPhysicalWidth() const
{
	return m_physicalWidth;
}

double Player::getPhysicalHeight() const
{
	return m_physicalHeight;
}

void Player::updateObjectToPhysicalDimensions(const Point &position)
{
	if (m_object != 0)
		delete m_object;

	m_object = new DynamicObject(m_simulator, position, m_physicalWidth, m_physicalHeight);
}
