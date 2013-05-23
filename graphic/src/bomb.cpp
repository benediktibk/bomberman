#include "bomb.h"
#include "bombstate.h"
#include "pointgraphic.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

using namespace Graphic;

Bomb::Bomb(QGraphicsScene &scene) :
	m_item(new QGraphicsRectItem(0))
{
	m_item->setRect(-10, -10, 20, 20);
	m_item->setBrush(QBrush(QColor(0, 0, 0)));
	m_item->setPen(QPen(QColor(0, 0, 0)));

	scene.addItem(m_item);
}

Bomb::~Bomb()
{
	delete m_item;
}

void Bomb::update(const Common::BombState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	m_item->setPos(position.toQPoint());
}
