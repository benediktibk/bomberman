#ifndef GRAPHIC_WALL_H
#define GRAPHIC_WALL_H

class QGraphicsScene;
class QGraphicsSvgItem;

namespace Common
{
	class WallState;
}

namespace Graphic
{
class Wall
{
public:
	Wall(QGraphicsScene &scene);
	~Wall();

	void update(const Common::WallState &state, double pixelPerMeter);

private:
	QGraphicsSvgItem *m_svgItem;
};
}

#endif
