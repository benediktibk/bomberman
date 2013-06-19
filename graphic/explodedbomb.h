#ifndef GRAPHIC_EXPLODEDBOMB_H
#define GRAPHIC_EXPLODEDBOMB_H

#include <vector>

class QGraphicsScene;
class QGraphicsSvgItem;

namespace Common
{
	class ExplodedBombState;
}

namespace Graphic
{
	class RenderAllSvgGraphics;
	class ExplodedBomb
	{
	public:
		ExplodedBomb(QGraphicsScene &scene, RenderAllSvgGraphics &renderer, const Common::ExplodedBombState &state, double pixelPerMeter);
		~ExplodedBomb();

	private:
		void createCenterFlame(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlameEnds(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheRight(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheLeft(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheUpper(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheLower(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);

	private:
		RenderAllSvgGraphics *m_renderer;
		QGraphicsSvgItem *m_center;
		QGraphicsSvgItem *m_upperEnd;
		QGraphicsSvgItem *m_lowerEnd;
		QGraphicsSvgItem *m_leftEnd;
		QGraphicsSvgItem *m_rightEnd;
		std::vector<QGraphicsSvgItem*> m_middleParts;
	};
}

#endif
