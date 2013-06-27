#include "wall.h"
#include "common/wallstate.h"
#include "graphic/point.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QGraphicsSvgItem>
#include <assert.h>

using namespace Graphic;

Wall::Wall(QGraphicsScene &scene, SvgRenderer &renderer, const Common::WallState &state)
{
	createSVGItem(state.getWallType(), renderer, state.getWidth());
	scene.addItem(m_svgItem);
}

Wall::Wall(QGraphicsScene &scene, SvgRenderer &renderer, const Common::Point &position, double pixelPerMeter, double dimension)
{
	createSVGItem(Common::WallState::WallTypeSolid, renderer, dimension);
	updateInternal(position, pixelPerMeter);
	scene.addItem(m_svgItem);
}

Wall::~Wall()
{
	delete m_svgItem;
}

void Wall::update(const Common::WallState &state, double pixelPerMeter)
{
	updateInternal(state.getPosition(), pixelPerMeter);
}

void Wall::createSVGItem(Common::WallState::WallType wallType, SvgRenderer &renderer, double dimension)
{
	if (wallType == Common::WallState::WallTypeSolid)
		m_svgItem = renderer.getNewSolidWallItem(dimension);
	else
		m_svgItem = renderer.getNewLooseWallItem(dimension);
	m_svgItem->setZValue(1);
}

void Wall::updateInternal(const Common::Point &position, double pixelPerMeter)
{
	Point positionScaled(position*pixelPerMeter);
	positionScaled.switchIntoQtCoordinates();
	m_svgItem->setPos(positionScaled.toQPoint());
}
