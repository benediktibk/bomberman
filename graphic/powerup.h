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
	class SvgRenderer;
	class PowerUp
	{
	public:
		PowerUp(QGraphicsScene &scene, SvgRenderer &renderer);
		PowerUp(QGraphicsScene &scene, SvgRenderer &renderer, Common::PowerUpState &state, double pixelPerMeter);
		~PowerUp();

		void update(const Common::PowerUpState &state, double pixelPerMeter);

	private:
		void createSvgItem(Common::PowerUpState &state, SvgRenderer &renderer);
		QGraphicsSvgItem *m_svgItem;
	};
}

#endif
