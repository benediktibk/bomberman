#include "cellbackground.h"
#include "graphic/point.h"
#include "QGraphicsScene"
#include "QtSvg/QtSvg"

using namespace Graphic;

CellBackground::CellBackground(QGraphicsScene &scene) :
    m_svgItem(new QGraphicsSvgItem)
{
    scene.addItem(m_svgItem);
}

CellBackground::~CellBackground()
{
    delete m_svgItem;
}

void CellBackground::update(const Point &point, double pixelPerMeter)
{
    Point position(point * pixelPerMeter);
    position.switchIntoQtCoordinates();

    m_svgItem->setScale(0.001*pixelPerMeter);
    m_svgItem->setPos(position.toQPoint());
}
