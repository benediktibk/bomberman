#ifndef GRAPHIC_WALL_H
#define GRAPHIC_WALL_H

#include "common/wallstate.h"

class QGraphicsScene;
class QGraphicsSvgItem;

namespace Graphic
{
class RenderAllSvgGraphics;
class Wall
{
public:
	Wall(QGraphicsScene &scene, RenderAllSvgGraphics &renderer, const Common::WallState &state);
	Wall(QGraphicsScene &scene, RenderAllSvgGraphics &renderer, const Common::Point &position, double pixelPerMeter);
	~Wall();

	void update(const Common::WallState &state, double pixelPerMeter);

private:
	void createSVGItem(Common::WallState::WallType wallType, RenderAllSvgGraphics &renderer);
	void updateInternal(const Common::Point &position, double width, double height, double pixelPerMeter);

private:
	QGraphicsSvgItem *m_svgItem;
};
}

#endif
