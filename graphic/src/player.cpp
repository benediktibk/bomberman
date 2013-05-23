#include "player.h"
#include "playerstate.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

using namespace Graphic;
using namespace Common;

Player::Player(QGraphicsScene &scene) :
	m_item(new QGraphicsRectItem(0))
{
	m_item->setRect(-10, -10, 20, 20);
	m_item->setBrush(QBrush(QColor(0, 0, 0)));
	m_item->setPen(QPen(QColor(0, 0, 0)));

	scene.addItem(m_item);
}

Player::~Player()
{
	delete m_item;
}

void Player::update(const PlayerState &state, double /*pixelPerMeter*/)
{
	m_item->setPos(-10, (-1)*state.getPosition() - 10);
}
