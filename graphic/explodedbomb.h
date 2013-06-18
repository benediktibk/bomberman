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
	class ExplodedBomb
	{
	public:
		ExplodedBomb(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter);
		~ExplodedBomb();

	private:
		QGraphicsSvgItem *m_center;
		QGraphicsSvgItem *m_upperEnd;
		QGraphicsSvgItem *m_lowerEnd;
		QGraphicsSvgItem *m_leftEnd;
		QGraphicsSvgItem *m_rightEnd;
		std::vector<QGraphicsSvgItem*> m_middleParts;
	};
}

#endif
