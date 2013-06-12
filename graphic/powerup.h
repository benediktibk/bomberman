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
	class PowerUp
	{
	public:
		PowerUp(QGraphicsScene &scene);
        PowerUp(QGraphicsScene &scene, Common::PowerUpState &state, double pixelPerMeter);
		~PowerUp();

		void update(const Common::PowerUpState &state, double pixelPerMeter);

	private:
        void createSvgItem(Common::PowerUpState &state);
		QGraphicsSvgItem *m_svgItem;
	};
}

#endif
