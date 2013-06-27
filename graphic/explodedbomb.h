#ifndef GRAPHIC_EXPLODEDBOMB_H
#define GRAPHIC_EXPLODEDBOMB_H

#include <vector>

class QGraphicsScene;
class QGraphicsItem;

namespace Common
{
	class ExplodedBombState;
}

namespace Graphic
{
	class SvgRenderer;
	class ExplodedBomb
	{
	public:
		ExplodedBomb(QGraphicsScene &scene, SvgRenderer &renderer, const Common::ExplodedBombState &state, double pixelPerMeter);
		~ExplodedBomb();

	private:
		void createCenterFlame(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlameEnds(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheRight(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheLeft(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheUpper(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		void createFlamesToTheLower(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);

	private:
		SvgRenderer *m_renderer;
		QGraphicsItem *m_center;
		QGraphicsItem *m_upperEnd;
		QGraphicsItem *m_lowerEnd;
		QGraphicsItem *m_leftEnd;
		QGraphicsItem *m_rightEnd;
		std::vector<QGraphicsItem*> m_middleParts;
	};
}

#endif
