#include "gridpoint.h"
#include <math.h>
#include "compare.h"

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
	Compare compare(0.05);
	if (compare.isFuzzyEqual((m_x + 1), point.getX()))
		++m_x;

	if (compare.isFuzzyEqual((m_y + 1), point.getY()))
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

std::vector<GridPoint> GridPoint::getCoveredGridPoints(Common::Point position)
{
	GridPoint positionGrid(position);
	vector<GridPoint> result;
	Compare compare(0.05);

	double x = position.getX();
	double y = position.getY();
	double xGrid = positionGrid.getX();
	double yGrid = positionGrid.getY();

	if (compare.isStrictFuzzyGreater(x, xGrid))
	{
		result.push_back(positionGrid);
		GridPoint positionGrid2(positionGrid.getX()+1,positionGrid.getY());
		result.push_back(positionGrid2);
	}

	if (compare.isStrictFuzzyGreater(y, yGrid))
	{
		result.push_back(positionGrid);
		GridPoint positionGrid2(positionGrid.getX(),positionGrid.getY()+1);
		result.push_back(positionGrid2);
	}

	if(compare.isFuzzyEqual(x, xGrid) && compare.isFuzzyEqual(y, yGrid))
	{
		result.push_back(positionGrid);
	}

	return result;
}
