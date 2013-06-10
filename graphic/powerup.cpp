#include "graphic/powerup.h"
#include "graphic/point.h"
#include "common/powerupstate.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;
using namespace Common;

PowerUp::PowerUp(QGraphicsScene &scene) :
	m_svgItem(new QGraphicsSvgItem(QString("resources/objects/power_up.svg")))
{
	scene.addItem(m_svgItem);
}

PowerUp::~PowerUp()
{
	delete m_svgItem;
}

void PowerUp::update(const PowerUpState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	position = position + Point(state.getWidth()/2, state.getHeight()/2);
	position.switchIntoQtCoordinates();

	m_svgItem->setScale(0.001*pixelPerMeter*state.getHeight());
	m_svgItem->setPos(position.toQPoint());
}
