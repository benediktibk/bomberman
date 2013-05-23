#include "wall.h"
#include "wallstate.h"
#include "pointgraphic.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

using namespace Graphic;

Wall::Wall(QGraphicsScene &scene) :
	m_item(new QGraphicsRectItem(0))
{
	m_item->setRect(-10, -10, 20, 20);
	m_item->setBrush(QBrush(QColor(0, 0, 0)));
	m_item->setPen(QPen(QColor(0, 0, 0)));

	scene.addItem(m_item);
}

Wall::~Wall()
{
	delete m_item;
}

void Wall::update(const Common::WallState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	m_item->setPos(position.toQPoint());
}