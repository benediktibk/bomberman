#ifndef GRAPHIC_BOMB_H
#define GRAPHIC_BOMB_H

class QGraphicsScene;
class QGraphicsSvgItem;

namespace Common
{
	class BombState;
}

namespace Graphic
{
	class RenderAllSvgGraphics;

	class Bomb
	{
	public:
		Bomb(QGraphicsScene &scene);
		Bomb(QGraphicsScene &scene, RenderAllSvgGraphics *renderer);
		~Bomb();

		void update(const Common::BombState &state, double pixelPerMeter);

	private:
		QGraphicsSvgItem *m_svgItem;
	};
}

#endif
