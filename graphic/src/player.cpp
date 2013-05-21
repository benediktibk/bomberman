#include "player.h"
#include "playerstate.h"
#include <QGraphicsRectItem>

using namespace Graphic;
using namespace Common;

Player::Player(QGraphicsScene &scene) :
	m_item(new QGraphicsRectItem(0, &scene))
{
	m_item->setRect(-10, -10, 20, 20);
}

Player::~Player()
{
	delete m_item;
}

void Player::update(const PlayerState &state)
{
	m_item->setPos(-10, (-1)*state.getPosition() - 10);
}
