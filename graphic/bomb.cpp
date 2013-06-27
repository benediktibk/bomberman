#include "bomb.h"
#include "common/bombstate.h"
#include "graphic/point.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;

Bomb::Bomb(QGraphicsScene &scene, SvgRenderer &renderer, const Common::BombState &state)
{
	m_svgItem = renderer.getNewBombItem(state.getWidth());
	scene.addItem(m_svgItem);
}

Bomb::~Bomb()
{
	delete m_svgItem;
}

void Bomb::update(const Common::BombState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	position.switchIntoQtCoordinates();
	m_svgItem->setPos(position.toQPoint());
}
