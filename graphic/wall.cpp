#include "wall.h"
#include "common/wallstate.h"
#include "graphic/point.h"
#include <QGraphicsScene>
#include <QtSvg/QGraphicsSvgItem>

using namespace Graphic;

Wall::Wall(QGraphicsScene &scene, const Common::WallState &state)
{
    if (state.getWallType() == Common::WallState::WallTypeSolid)
        m_svgItem = new QGraphicsSvgItem(QString("../../resources/objects/wall_solid.svg"));
    else
        m_svgItem = new QGraphicsSvgItem(QString("../../resources/objects/wall_loose.svg"));

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

    m_svgItem->setScale(0.001*pixelPerMeter*state.getWallHeight());
	m_svgItem->setPos(position.toQPoint());
}
