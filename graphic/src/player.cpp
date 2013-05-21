#include "player.h"
#include <QGraphicsRectItem>

using namespace Graphic;

Player::Player(QGraphicsScene &scene) :
	m_item(new QGraphicsRectItem(0, &scene))
{
	m_item->setRect(-10, -10, 20, 20);
}

Player::~Player()
{
	delete m_item;
}
