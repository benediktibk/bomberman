#include "bomb.h"
#include "common/bombstate.h"
#include "graphic/point.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;

Bomb::Bomb(QGraphicsScene &scene) :
	m_svgItem(new QGraphicsSvgItem(QString("resources/graphics/bomb_planted.svg")))
{
	m_svgItem->setZValue(1);
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
