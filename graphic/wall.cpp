#include "wall.h"
#include "common/wallstate.h"
#include "graphic/point.h"
#include <QGraphicsScene>
#include <QtSvg/QGraphicsSvgItem>

using namespace Graphic;

Wall::Wall(QGraphicsScene &scene, const Common::WallState &state)
{
	createSVGItem(state.getWallType());
	scene.addItem(m_svgItem);
}

Wall::Wall(QGraphicsScene &scene, const Common::Point &position, double pixelPerMeter)
{
	createSVGItem(Common::WallState::WallTypeSolid);
	updateInternal(position, 1, 1, pixelPerMeter);
	scene.addItem(m_svgItem);
}

Wall::~Wall()
{
	delete m_svgItem;
}

void Wall::update(const Common::WallState &state, double pixelPerMeter)
{
	updateInternal(state.getPosition(), state.getWidth(), state.getHeight(), pixelPerMeter);
}

void Wall::createSVGItem(Common::WallState::WallType wallType)
{
	if (wallType == Common::WallState::WallTypeSolid)
		m_svgItem = new QGraphicsSvgItem(QString("resources/objects/wall_solid.svg"));
	else
		m_svgItem = new QGraphicsSvgItem(QString("resources/objects/wall_loose.svg"));
}

void Wall::updateInternal(const Common::Point &position, double width, double height, double pixelPerMeter)
{
	Point positionScaled(position*pixelPerMeter);
	positionScaled = positionScaled + Point(width/2, height/2)*pixelPerMeter;
	positionScaled.switchIntoQtCoordinates();

	m_svgItem->setScale(0.001*pixelPerMeter*height);
	m_svgItem->setPos(positionScaled.toQPoint());
}
