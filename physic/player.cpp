#include "physic/player.h"
#include "physic/physicalobject.h"
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "common/playerstate.h"
#include <assert.h>

using namespace Common;
using namespace Physic;
using namespace std;

Player::Player(PhysicSimulator &simulator, const PlayerState &player) :
	m_simulator(simulator),
	m_object(0),
	m_dynamicObject(0),
	m_staticObject(0),
	m_width(player.getWidth()),
	m_height(player.getHeight()),
	m_physicalWidth(m_width),
	m_physicalHeight(m_height),
	m_movingIntoX(false),
	m_movingIntoY(false)
{
	int16_t playerID = player.getId();
	int16_t collisionGroup = (-1)*(playerID + 1);
	updateObjectToPhysicalDimensions(player.getPosition(), collisionGroup);
}

Player::~Player()
{
	if (m_object != 0)
		delete m_object;

	m_object = 0;
	m_dynamicObject = 0;
	m_staticObject = 0;
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
    delete m_field1;
    delete m_field2;
    m_field1 = 0;
    m_field2 = 0;

	Point oldPosition = getPosition();
    vector<GridPoint> coverdFields = GridPoint::getCoveredGridPoints(oldPosition);	Point newPosition;

	if (velocityIntoX != 0)
	{
		m_physicalWidth = m_width;
		m_physicalHeight = m_height/2;
		m_movingIntoX = true;
		m_movingIntoY = false;
		newPosition = oldPosition + Point(0, m_height/4);
        if (coverdFields.size() == 1)
            m_field1 = new StaticObject(m_simulator,coverdFields[0].getPointPosition(),1.0,1.0);
        else
        {
            m_field1 = new StaticObject(m_simulator,coverdFields[0].getPointPosition(),1.0,1.0);
            m_field1 = new StaticObject(m_simulator,coverdFields[1].getPointPosition(),1.0,1.0);
        }
	}
	else if (velocityIntoY != 0)
	{
		m_physicalWidth = m_width/2;
		m_physicalHeight = m_height;
		m_movingIntoX = false;
		m_movingIntoY = true;
		newPosition = oldPosition + Point(m_width/4, 0);
        if (coverdFields.size() == 1)
            m_field1 = new StaticObject(m_simulator,coverdFields[0].getPointPosition(),1.0,1.0);
        else
        {
            m_field1 = new StaticObject(m_simulator,coverdFields[0].getPointPosition(),1.0,1.0);
            m_field1 = new StaticObject(m_simulator,coverdFields[1].getPointPosition(),1.0,1.0);
        }
	}
	else
	{
		m_physicalHeight = m_height;
		m_physicalWidth = m_width;
		m_movingIntoX = false;
		m_movingIntoY = false;
		newPosition = oldPosition;
	}

	updateObjectToPhysicalDimensions(newPosition, m_object->getCollisionGroup());
	if (isMoving())
		m_dynamicObject->applyLinearVelocity(velocityIntoX, velocityIntoY);

	assert(oldPosition.fuzzyEqual(getPosition(), 0.0001));
}

double Player::getVelocityX() const
{
	assert(m_object != 0);

	if (isMoving())
		return m_dynamicObject->getVelocityX();
	else
		return 0;
}

double Player::getVelocityY() const
{
	assert(m_object != 0);

	if (isMoving())
		return m_dynamicObject->getVelocityY();
	else
		return 0;
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

bool Player::isMoving() const
{
	return m_movingIntoX || m_movingIntoY;
}

void Player::updateObjectToPhysicalDimensions(const Point &position, int16_t collisionGroup)
{
	if (m_object != 0)
		delete m_object;

	m_object = 0;
	m_dynamicObject = 0;
	m_staticObject = 0;

	if (isMoving())
	{
		m_dynamicObject = new DynamicObject(m_simulator, position, m_physicalWidth, m_physicalHeight);
		m_object = m_dynamicObject;
	}
	else
	{
		m_staticObject = new StaticObject(m_simulator, position, m_physicalWidth, m_physicalHeight);
		m_object = m_staticObject;
	}

	m_object->setCollisionGroup(collisionGroup);
}


