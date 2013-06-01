#ifndef COMMON_GRIDPOINT_H
#define COMMON_GRIDPOINT_H

#include "point.h"

namespace Common
{
class GridPoint
{
public:
	GridPoint();
	GridPoint(unsigned int x, unsigned int y);
	GridPoint(const Point &point);
	void setX(unsigned int value);
	unsigned int getX() const;
	void setY(unsigned int value);
	unsigned int getY() const;

	bool operator==(const GridPoint &gridPoint) const;
	GridPoint operator*(unsigned int value) const;
	GridPoint operator/(unsigned int value) const;
	GridPoint operator+(const GridPoint &gridPoint) const;
	GridPoint operator-(const GridPoint &gridPoint) const;
	Point getPointPosition() const;

private:
	unsigned int m_x;
	unsigned int m_y;
};
}

std::ostream& operator<<(std::ostream &stream, const Common::GridPoint &point);

#endif
