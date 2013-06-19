#include "player.h"
#include "graphic/point.h"
#include "common/playerstate.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>


using namespace Graphic;
using namespace Common;

Player::Player(QGraphicsScene &scene) :
	m_svgItem(new QGraphicsSvgItem(QString("resources/graphics/player_standing.svg")))
{
	m_svgItem->setZValue(2);
	scene.addItem(m_svgItem);
}

Player::Player(QGraphicsScene &scene, SvgRenderer &renderer)
{
	m_svgItem = renderer.getNewPlayerItem();
	scene.addItem(m_svgItem);
}

Player::~Player()
{
	delete m_svgItem;
}

void Player::update(const PlayerState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	position.switchIntoQtCoordinates();

	m_svgItem->setScale(0.001*pixelPerMeter*state.getWidth());
	m_svgItem->setPos(position.toQPoint());
}
