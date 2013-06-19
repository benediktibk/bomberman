#ifndef GRAPHIC_POWERUP_H
#define GRAPHIC_POWERUP_H

class QGraphicsScene;
class QGraphicsSvgItem;

namespace Common
{
	class PowerUpState;
}

namespace Graphic
{
	class RenderAllSvgGraphics;
	class PowerUp
	{
	public:
		PowerUp(QGraphicsScene &scene, RenderAllSvgGraphics &renderer);
		PowerUp(QGraphicsScene &scene, RenderAllSvgGraphics &renderer, Common::PowerUpState &state, double pixelPerMeter);
		~PowerUp();

		void update(const Common::PowerUpState &state, double pixelPerMeter);

	private:
		void createSvgItem(Common::PowerUpState &state, RenderAllSvgGraphics &renderer);
		QGraphicsSvgItem *m_svgItem;
	};
}

#endif
