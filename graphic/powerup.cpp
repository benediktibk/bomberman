#include "graphic/powerup.h"
#include "graphic/point.h"
#include "common/powerupstate.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>

using namespace Graphic;
using namespace Common;

PowerUp::PowerUp(QGraphicsScene &scene, SvgRenderer &renderer, const PowerUpState &state, double pixelPerMeter) :
	m_graphicItem(renderer.getNewPowerUpItem(state.getPowerUpType(), state.getWidth()))
{
	m_graphicItem->setZValue(0);
	scene.addItem(m_graphicItem);
	update(state, pixelPerMeter);
}

PowerUp::~PowerUp()
{
	delete m_graphicItem;
}

void PowerUp::update(const PowerUpState &state, double pixelPerMeter)
{
	Point position(state.getPosition()*pixelPerMeter);
	position.switchIntoQtCoordinates();
	m_graphicItem->setPos(position.toQPoint());
}
