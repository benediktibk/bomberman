#include "wall.h"
#include "wallstate.h"
#include "pointgraphic.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

using namespace Graphic;

Wall::Wall(QGraphicsScene &scene) :
	m_item(new QGraphicsRectItem(0))
{
	m_item->setBrush(QBrush(QColor(105, 105, 105)));
	m_item->setPen(QPen(QColor(105, 105, 105)));

	scene.addItem(m_item);
}

Wall::~Wall()
{
	delete m_item;
}

void Wall::update(const Common::WallState &state, double pixelPerMeter)
{
	m_item->setRect(0, 0, 1*pixelPerMeter, 1*pixelPerMeter);
	Point position(state.getPosition()*pixelPerMeter);
	position.switchIntoQtCoordinates();
	m_item->setPos(position.toQPoint());
}