#include "gridpoint.h"
#include <math.h>

using namespace Common;
using namespace std;

GridPoint::GridPoint() :
	m_x(0),
	m_y(0)
{ }

GridPoint::GridPoint(unsigned int x, unsigned int y) :
	m_x(x),
	m_y(y)
{ }

GridPoint::GridPoint(const Point &point) :
		m_x(static_cast<unsigned int>(point.getX())),
		m_y(static_cast<unsigned int>(point.getY()))
{

	//! @todo replace with fuzzy
	if (fabs((m_x + 1) - point.getX()) < 0.05)
		++m_x;

	//! @todo replace with fuzzy
	if (fabs((m_y + 1) - point.getY()) < 0.05)
		++m_y;
}

void GridPoint::setX(unsigned int value)
{
	m_x = value;
}

unsigned int GridPoint::getX() const
{
	return m_x;
}

void GridPoint::setY(unsigned int value)
{
	m_y = value;
}

unsigned int GridPoint::getY() const
{
	return m_y;
}

bool GridPoint::operator ==(const GridPoint &gridPoint) const
{
	return	getX() == gridPoint.getX() &&
			getY() == gridPoint.getY();
}

GridPoint GridPoint::operator *(unsigned int value) const
{
	return GridPoint(m_x*value, m_y*value);
}

GridPoint GridPoint::operator /(unsigned int value) const
{
	return GridPoint(m_x/value, m_y/value);
}

GridPoint GridPoint::operator+(const GridPoint &gridPoint) const
{
	return GridPoint(getX() + gridPoint.getX(), getY() + gridPoint.getY());
}

GridPoint GridPoint::operator-(const GridPoint &gridPoint) const
{
	return GridPoint(getX() - gridPoint.getX(), getY() - gridPoint.getY());
}

Point GridPoint::getPointPosition() const
{
	Point point;
	double x = static_cast<double>(m_x);
	double y = static_cast<double>(m_y);
	point.setX(x);
	point.setY(y);


	return point;
}

ostream& operator<<(ostream &stream, const GridPoint &point)
{
	stream << "(" << point.getX() << ", " << point.getY() << ")";
	return stream;
}


