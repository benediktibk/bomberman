#include "player.h"
#include "graphic/point.h"
#include "common/playerstate.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;
using namespace Common;

Player::Player(QGraphicsScene &scene, SvgRenderer &renderer, const PlayerState &state) :
	m_standing(renderer.getNewPlayerStandingItem(state.getId(), state.getWidth())),
	m_movingLeft(renderer.getNewPlayerMovingLeftItem(state.getId(), state.getWidth())),
	m_movingUp(renderer.getNewPlayerMovingUpItem(state.getId(), state.getWidth())),
	m_movingRight(renderer.getNewPlayerMovingRightItem(state.getId(), state.getWidth())),
	m_movingDown(renderer.getNewPlayerMovingDownItem(state.getId(), state.getWidth()))
{
	m_standing->setZValue(2);
	m_movingLeft->setZValue(2);
	m_movingUp->setZValue(2);
	m_movingRight->setZValue(2);
	m_movingDown->setZValue(2);
	scene.addItem(m_standing);
	scene.addItem(m_movingLeft);
	scene.addItem(m_movingUp);
	scene.addItem(m_movingRight);
	scene.addItem(m_movingDown);
	m_movingLeft->hide();
	m_movingUp->hide();
	m_movingRight->hide();
	m_movingDown->hide();
}

Player::~Player()
{
	delete m_standing;
	delete m_movingLeft;
	delete m_movingUp;
	delete m_movingRight;
	delete m_movingDown;
}

void Player::update(const PlayerState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	position.switchIntoQtCoordinates();
	QPointF qtPosition = position.toQPoint();

	m_standing->setPos(qtPosition);
	m_movingLeft->setPos(qtPosition);
	m_movingUp->setPos(qtPosition);
	m_movingRight->setPos(qtPosition);
	m_movingDown->setPos(qtPosition);
	m_standing->hide();
	m_movingLeft->hide();
	m_movingUp->hide();
	m_movingRight->hide();
	m_movingDown->hide();

	switch(state.getDirection())
	{
	case PlayerState::PlayerDirectionLeft:
		m_movingLeft->show();
		break;
	case PlayerState::PlayerDirectionUp:
		m_movingUp->show();
		break;
	case PlayerState::PlayerDirectionRight:
		m_movingRight->show();
		break;
	case PlayerState::PlayerDirectionDown:
		m_movingDown->show();
		break;
	case PlayerState::PlayerDirectionNone:
		m_standing->show();
		break;
	}
}
