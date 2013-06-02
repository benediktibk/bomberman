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
	m_physicalHeight(height),
	m_movingIntoX(false),
	m_movingIntoY(false)
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

	Point objectPosition = m_object->getPosition();

	if (m_movingIntoX)
		return objectPosition - Point(0, m_height/4);
	else if (m_movingIntoY)
		return objectPosition - Point(m_width/4, 0);
	else
		return objectPosition;
}

Point Player::getCenterPosition() const
{
	assert(m_object != 0);
	return m_object->getCenterPosition();
}

void Player::applyLinearVelocity(double velocityIntoX, double velocityIntoY)
{
	assert(velocityIntoX == 0 || velocityIntoY == 0);

	Point oldPosition = getPosition();
	Point newPosition;

	if (velocityIntoX != 0)
	{
		m_physicalWidth = m_width;
		m_physicalHeight = m_height/2;
		m_movingIntoX = true;
		m_movingIntoY = false;
		newPosition = oldPosition + Point(0, m_height/4);
	}
	else if (velocityIntoY != 0)
	{
		m_physicalWidth = m_width/2;
		m_physicalHeight = m_height;
		m_movingIntoX = false;
		m_movingIntoY = true;
		newPosition = oldPosition + Point(m_width/4, 0);
	}
	else
	{
		m_physicalHeight = m_height;
		m_physicalWidth = m_width;
		m_movingIntoX = false;
		m_movingIntoY = false;
		newPosition = oldPosition;
	}

	updateObjectToPhysicalDimensions(newPosition);
	m_object->applyLinearVelocity(velocityIntoX, velocityIntoY);

	assert(oldPosition.fuzzyEqual(getPosition(), 0.0001));
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
