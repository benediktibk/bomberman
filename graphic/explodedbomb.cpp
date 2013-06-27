#include "graphic/explodedbomb.h"
#include "common/explodedbombstate.h"
#include "graphic/point.h"
#include "graphic/svgrenderer.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>
#include <assert.h>

using namespace Graphic;
using namespace std;

ExplodedBomb::ExplodedBomb(QGraphicsScene &scene, SvgRenderer &renderer, const Common::ExplodedBombState &state, double pixelPerMeter) :
	m_renderer(&renderer),
	m_center(0),
	m_upperEnd(0),
	m_lowerEnd(0),
	m_leftEnd(0),
	m_rightEnd(0)
{
	assert(state.getHeight() == state.getWidth());

	createCenterFlame(scene, state, pixelPerMeter);
	createFlameEnds(scene, state, pixelPerMeter);
	createFlamesToTheLeft(scene, state, pixelPerMeter);
	createFlamesToTheLower(scene, state, pixelPerMeter);
	createFlamesToTheRight(scene, state, pixelPerMeter);
	createFlamesToTheUpper(scene, state, pixelPerMeter);
}

ExplodedBomb::~ExplodedBomb()
{
	delete m_center;
	delete m_upperEnd;
	delete m_leftEnd;
	delete m_lowerEnd;
	delete m_rightEnd;

	for (vector<QGraphicsItem*>::iterator i = m_middleParts.begin(); i != m_middleParts.end(); ++i)
		delete *i;
	m_middleParts.clear();
}

void ExplodedBomb::createCenterFlame(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter)
{
	m_center = m_renderer->getNewExplodedBombCenterItem(state.getWidth());
	Point centerPosition(state.getPosition());
	centerPosition *= pixelPerMeter;
	centerPosition.switchIntoQtCoordinates();
	m_center->setPos(centerPosition.toQPoint());
	m_center->setZValue(5.5);
	scene.addItem(m_center);
}

void ExplodedBomb::createFlameEnds(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter)
{
	double dimension = state.getWidth();

	m_upperEnd = m_renderer->getNewExplodedBombEndItem(dimension);
	m_lowerEnd = m_renderer->getNewExplodedBombEndItem(dimension);
	m_leftEnd = m_renderer->getNewExplodedBombEndItem(dimension);
	m_rightEnd = m_renderer->getNewExplodedBombEndItem(dimension);

	m_lowerEnd->setRotation(180);
	m_leftEnd->setRotation(-90);
	m_rightEnd->setRotation(90);

	Point rightEndPosition(state.getPosition() + Point((state.getDestructionRangeRight() + 1)*dimension, 0));
	Point leftEndPosition(state.getPosition() + Point((-1.0)*(state.getDestructionRangeLeft())*dimension, (-1.0)*dimension));
	Point upperEndPosition(state.getPosition() + Point(0, state.getDestructionRangeUp()*dimension));
	Point lowerEndPosition(state.getPosition() + Point(dimension, (-1.0)*(state.getDestructionRangeDown() + 1)*dimension));

	rightEndPosition *= pixelPerMeter;
	leftEndPosition *= pixelPerMeter;
	upperEndPosition *= pixelPerMeter;
	lowerEndPosition *= pixelPerMeter;

	rightEndPosition.switchIntoQtCoordinates();
	leftEndPosition.switchIntoQtCoordinates();
	upperEndPosition.switchIntoQtCoordinates();
	lowerEndPosition.switchIntoQtCoordinates();

	m_leftEnd->setPos(leftEndPosition.toQPoint());
	m_rightEnd->setPos(rightEndPosition.toQPoint());
	m_lowerEnd->setPos(lowerEndPosition.toQPoint());
	m_upperEnd->setPos(upperEndPosition.toQPoint());

	m_leftEnd->setZValue(5);
	m_rightEnd->setZValue(5);
	m_lowerEnd->setZValue(5);
	m_upperEnd->setZValue(5);

	scene.addItem(m_upperEnd);
	scene.addItem(m_leftEnd);
	scene.addItem(m_rightEnd);
	scene.addItem(m_lowerEnd);
}

void ExplodedBomb::createFlamesToTheRight(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter)
{
	double dimension = state.getWidth();
	unsigned int destructionRange = state.getDestructionRangeRight();

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsItem *item = m_renderer->getNewExplodedBombFlameItem(dimension);
		item->setRotation(-90);
		Point position(state.getPosition() + Point(i, (-1)*dimension));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		scene.addItem(item);
		m_middleParts.push_back(item);
	}
}

void ExplodedBomb::createFlamesToTheLeft(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter)
{
	double dimension = state.getWidth();
	unsigned int destructionRange = state.getDestructionRangeLeft();

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsItem *item = m_renderer->getNewExplodedBombFlameItem(dimension);
		item->setRotation(90);
		Point position(state.getPosition() + Point((-1.0)*i + dimension, 0));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		scene.addItem(item);
		m_middleParts.push_back(item);
	}
}

void ExplodedBomb::createFlamesToTheUpper(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter)
{
	double dimension = state.getWidth();
	unsigned int destructionRange = state.getDestructionRangeUp();

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsItem *item = m_renderer->getNewExplodedBombFlameItem(dimension);
		Point position(state.getPosition() + Point(0, i));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		scene.addItem(item);
		m_middleParts.push_back(item);
	}
}

void ExplodedBomb::createFlamesToTheLower(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter)
{
	double dimension = state.getWidth();
	unsigned int destructionRange = state.getDestructionRangeDown();

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsItem *item = m_renderer->getNewExplodedBombFlameItem(dimension);
		item->setRotation(180);
		Point position(state.getPosition() + Point(dimension, (-1)*(dimension + i)));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		scene.addItem(item);
		m_middleParts.push_back(item);
	}
}
