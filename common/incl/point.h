#ifndef POINT_H
#define POINT_H

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

private:
	double m_x;
	double m_y;
};
}

#endif
