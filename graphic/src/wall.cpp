#include "wall.h"
#include "wallstate.h"
#include "pointgraphic.h"
#include <QGraphicsScene>
#include <QtSvg/QGraphicsSvgItem>

using namespace Graphic;

Wall::Wall(QGraphicsScene &scene) :
    m_svgItem(new QGraphicsSvgItem(QString("../../resources/objects/wall_solid.svg")))
{

    scene.addItem(m_svgItem);

}

Wall::~Wall()
{
    delete m_svgItem;
}

void Wall::update(const Common::WallState &state, double pixelPerMeter)
{
    Point position(state.getPosition()*pixelPerMeter);
    position.switchIntoQtCoordinates();

    m_svgItem->setScale(0.001*pixelPerMeter);
    m_svgItem->setPos(position.toQPoint());
}
