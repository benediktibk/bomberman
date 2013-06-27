#include "graphic/powerup.h"
#include "graphic/point.h"
#include "common/powerupstate.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;
using namespace Common;

PowerUp::PowerUp(QGraphicsScene &scene, SvgRenderer &renderer, const PowerUpState &state, double pixelPerMeter)
{
	createSvgItem(state, renderer);
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

void PowerUp::createSvgItem(const PowerUpState &state, SvgRenderer &renderer)
{
	m_svgItem = renderer.getNewPowerUpItem(state.getPowerUpType());
	m_svgItem->setZValue(0);
}
