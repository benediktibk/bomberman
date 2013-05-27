#include "pointgraphic.h"

using namespace Graphic;

Point::Point()
{ }

Point::Point(double x, double y) :
	Common::Point(x, y)
{ }

Point::Point(const Common::Point &point) :
	Common::Point(point)
{ }

QPointF Point::toQPoint() const
{
	return QPointF(getX(), getY());
}

void Point::switchIntoQtCoordinates()
{
	setY((-1)*getY());
}
