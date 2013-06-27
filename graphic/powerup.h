#ifndef GRAPHIC_POWERUP_H
#define GRAPHIC_POWERUP_H

class QGraphicsScene;
class QGraphicsItem;

namespace Common
{
	class PowerUpState;
}

namespace Graphic
{
	class SvgRenderer;
	class PowerUp
	{
	public:
		PowerUp(QGraphicsScene &scene, SvgRenderer &renderer, const Common::PowerUpState &state, double pixelPerMeter);
		~PowerUp();

		void update(const Common::PowerUpState &state, double pixelPerMeter);

	private:
		QGraphicsItem *m_graphicItem;
	};
}

#endif
