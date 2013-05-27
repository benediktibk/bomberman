#include "point.h"

using namespace Common;
using namespace std;

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

bool Point::operator ==(const Point &point) const
{
	return	getX() == point.getX() &&
			getY() == point.getY();
}

Point Point::operator *(double value) const
{
	return Point(m_x*value, m_y*value);
}

Point Point::operator /(double value) const
{
	return Point(m_x/value, m_y/value);
}

ostream& operator<<(ostream &stream, const Point &point)
{
	stream << "(" << point.getX() << ", " << point.getY() << ")";
	return stream;
}
