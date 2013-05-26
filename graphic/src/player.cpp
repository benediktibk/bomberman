#include "player.h"
#include "pointgraphic.h"
#include "playerstate.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>


using namespace Graphic;
using namespace Common;

Player::Player(QGraphicsScene &scene) :
    m_svgItem(new QGraphicsSvgItem(QString("../../resources/objects/player_standing.svg")))
{

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

    m_svgItem->setScale(0.001*pixelPerMeter);
    m_svgItem->setPos(position.toQPoint());
}
