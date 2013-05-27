#ifndef COMMON_POINT_H
#define COMMON_POINT_H

#include <ostream>

namespace Common
{
class Point
{
public:
	Point();
	Point(double x, double y);

	void setX(double value);
	double getX() const;
	void setY(double value);
	double getY() const;

	bool operator==(const Point &point) const;
	Point operator*(double value) const;
	Point operator/(double value) const;

private:
	double m_x;
	double m_y;
};
}

std::ostream& operator<<(std::ostream &stream, const Common::Point &point);

#endif
