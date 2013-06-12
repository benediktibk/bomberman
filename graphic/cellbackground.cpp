#include "cellbackground.h"
#include "graphic/point.h"
#include "QGraphicsScene"
#include "QtSvg/QtSvg"

using namespace Graphic;

CellBackground::CellBackground(QGraphicsScene &scene) :
    m_svgItem(new QGraphicsSvgItem(QString("resources/backgrounds/cell_pattern_1.svg")))
{
    scene.addItem(m_svgItem);
}

CellBackground::CellBackground(QGraphicsScene &scene, const Common::Point &position, double pixelPerMeter) :
    m_svgItem(new QGraphicsSvgItem(QString("resources/backgrounds/cell_pattern_1.svg")))
{
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
