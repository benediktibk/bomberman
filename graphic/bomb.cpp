#include "bomb.h"
#include "common/bombstate.h"
#include "graphic/point.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;

Bomb::Bomb(QGraphicsScene &scene) :
	m_svgItem(new QGraphicsSvgItem(QString("resources/graphics/bomb_planted.svg")))
{
	m_svgItem->setZValue(1);
	scene.addItem(m_svgItem);
}

Bomb::Bomb(QGraphicsScene &scene, SvgRenderer &renderer)
{
	m_svgItem = renderer.getNewBombItem();
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

	m_svgItem->setScale(0.001*pixelPerMeter*state.getHeight());
	m_svgItem->setPos(position.toQPoint());
}
