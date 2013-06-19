#include "cellbackground.h"
#include "graphic/point.h"
#include "graphic/svgrenderer.h"
#include "QGraphicsScene"
#include "QtSvg/QtSvg"

using namespace Graphic;

CellBackground::CellBackground(QGraphicsScene &scene, SvgRenderer &renderer) :
	m_svgItem(renderer.getNewCellBackgroundItem())
{
	m_svgItem->setZValue(-5);
    scene.addItem(m_svgItem);
}

CellBackground::CellBackground(QGraphicsScene &scene, SvgRenderer &renderer, const Common::Point &position, double pixelPerMeter) :
	m_svgItem(renderer.getNewCellBackgroundItem())
{
	m_svgItem->setZValue(-5);
    updateInternal(position, 1, 1, pixelPerMeter);
    scene.addItem(m_svgItem);
}

CellBackground::~CellBackground()
{
    delete m_svgItem;
}

void CellBackground::updateInternal(const Common::Point &position, double width, double height, double pixelPerMeter)
{
    Point positionScaled(position*pixelPerMeter);
    positionScaled = positionScaled + Point(width/2, height/2);
    positionScaled.switchIntoQtCoordinates();

    m_svgItem->setScale(0.001*pixelPerMeter*height);
    m_svgItem->setPos(positionScaled.toQPoint());
}

void CellBackground::update(const Common::Point &position, double pixelPerMeter)
{
    updateInternal(position, 1, 1, pixelPerMeter);
}
