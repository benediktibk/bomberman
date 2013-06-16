#include "graphic/powerup.h"
#include "graphic/point.h"
#include "common/powerupstate.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;
using namespace Common;

PowerUp::PowerUp(QGraphicsScene &scene) :
	m_svgItem(new QGraphicsSvgItem(QString("resources/graphics/powerup.svg")))
{
	scene.addItem(m_svgItem);
}

PowerUp::PowerUp(QGraphicsScene &scene, PowerUpState &state, double pixelPerMeter)
{
	createSvgItem(state);
	scene.addItem(m_svgItem);
	update(state, pixelPerMeter);
}

PowerUp::~PowerUp()
{
	delete m_svgItem;
}

void PowerUp::update(const PowerUpState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	position.switchIntoQtCoordinates();

	m_svgItem->setScale(0.001*pixelPerMeter*state.getHeight());
	m_svgItem->setPos(position.toQPoint());
}

void PowerUp::createSvgItem(PowerUpState &/*state*/)
{
	m_svgItem = new QGraphicsSvgItem(QString("resources/objects/powerup_v2.svg"));
}
