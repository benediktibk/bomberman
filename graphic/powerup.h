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
		~PowerUp();

		void update(const Common::PowerUpState &state, double pixelPerMeter);

	private:
		QGraphicsSvgItem *m_svgItem;
	};
}

#endif
