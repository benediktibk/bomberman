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
	scene.addItem(m_graphicItem);
}

Wall::Wall(QGraphicsScene &scene, SvgRenderer &renderer, const Common::Point &position, double pixelPerMeter, double dimension)
{
	createSVGItem(Common::WallState::WallTypeSolid, renderer, dimension);
	updateInternal(position, pixelPerMeter);
	scene.addItem(m_graphicItem);
}

Wall::~Wall()
{
	delete m_graphicItem;
}

void Wall::update(const Common::WallState &state, double pixelPerMeter)
{
	updateInternal(state.getPosition(), pixelPerMeter);
}

void Wall::createSVGItem(Common::WallState::WallType wallType, SvgRenderer &renderer, double dimension)
{
	if (wallType == Common::WallState::WallTypeSolid)
		m_graphicItem = renderer.getNewSolidWallItem(dimension);
	else
		m_graphicItem = renderer.getNewLooseWallItem(dimension);
	m_graphicItem->setZValue(1);
}

void Wall::updateInternal(const Common::Point &position, double pixelPerMeter)
{
	Point positionScaled(position*pixelPerMeter);
	positionScaled.switchIntoQtCoordinates();
	m_graphicItem->setPos(positionScaled.toQPoint());
}
