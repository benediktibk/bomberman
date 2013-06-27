#ifndef GRAPHIC_CELLBACKGROUND_H
#define GRAPHIC_CELLBACKGROUND_H

#include "common/point.h"

class QGraphicsScene;
class QGraphicsItem;


namespace Graphic
{
	class SvgRenderer;

	class CellBackground
	{
	public:
		CellBackground(QGraphicsScene &scene, SvgRenderer &renderer);
		CellBackground(QGraphicsScene &scene, SvgRenderer &renderer, const Common::Point &position, double pixelPerMeter);
		~CellBackground();

		void update(const Common::Point &position, double pixelPerMeter);

	private:
		void updateInternal(const Common::Point &position, double width, double height, double pixelPerMeter);
		QGraphicsItem *m_svgItem;
	};
}

#endif
