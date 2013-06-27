#ifndef GRAPHIC_BOMB_H
#define GRAPHIC_BOMB_H

class QGraphicsScene;
class QGraphicsItem;

namespace Common
{
	class BombState;
}

namespace Graphic
{
	class SvgRenderer;

	class Bomb
	{
	public:
		Bomb(QGraphicsScene &scene, SvgRenderer &renderer, const Common::BombState &state);
		~Bomb();

		void update(const Common::BombState &state, double pixelPerMeter);

	private:
		QGraphicsItem *m_svgItem;
	};
}

#endif
