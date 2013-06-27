#ifndef GRAPHIC_WALL_H
#define GRAPHIC_WALL_H

#include "common/wallstate.h"

class QGraphicsScene;
class QGraphicsItem;

namespace Graphic
{
	class SvgRenderer;

	class Wall
	{
	public:
		Wall(QGraphicsScene &scene, SvgRenderer &renderer, const Common::WallState &state);
		Wall(QGraphicsScene &scene, SvgRenderer &renderer, const Common::Point &position, double pixelPerMeter);
		~Wall();

		void update(const Common::WallState &state, double pixelPerMeter);

	private:
		void createSVGItem(Common::WallState::WallType wallType, SvgRenderer &renderer);
		void updateInternal(const Common::Point &position, double width, double height, double pixelPerMeter);

	private:
		QGraphicsItem *m_svgItem;
	};
}

#endif
