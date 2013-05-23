#include "point.h"

using namespace Common;

Point::Point() :
	m_x(0),
	m_y(0)
{ }

Point::Point(double x, double y) :
	m_x(x),
	m_y(y)
{ }

void Point::setX(double value)
{
	m_x = value;
}

double Point::getX() const
{
	return m_x;
}

void Point::setY(double value)
{
	m_y = value;
}

double Point::getY() const
{
	return m_y;
}
