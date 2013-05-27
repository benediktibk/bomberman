#ifndef GRAPHIC_POINTGRAPHIC_H
#define GRAPHIC_POINTGRAPHIC_H

#include "point.h"
#include <QPointF>

namespace Graphic
{
class Point :
		public Common::Point
{
public:
	Point();
	Point(double x, double y);
	Point(const Common::Point &point);

	QPointF toQPoint() const;
	void switchIntoQtCoordinates();
};
}

#endif
