#include "graphic/explodedbomb.h"
#include "common/explodedbombstate.h"
#include "graphic/point.h"
#include <QGraphicsScene>
#include <QtSvg/QtSvg>
#include <assert.h>

using namespace Graphic;
using namespace std;

ExplodedBomb::ExplodedBomb(QGraphicsScene &scene, const Common::ExplodedBombState &state, double pixelPerMeter) :
	m_center(new QGraphicsSvgItem(QString("resources/graphics/explosion_center.svg"))),
	m_upperEnd(new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"))),
	m_lowerEnd(new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"))),
	m_leftEnd(new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"))),
	m_rightEnd(new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg")))
{
	assert(state.getHeight() == state.getWidth());
	double dimension = state.getHeight();
	unsigned int destructionRange = state.getDesructionRange();

	m_center->setScale(0.001*pixelPerMeter*dimension);
	m_upperEnd->setScale(0.001*pixelPerMeter*dimension);
	m_leftEnd->setScale(0.001*pixelPerMeter*dimension);
	m_rightEnd->setScale(0.001*pixelPerMeter*dimension);
	m_lowerEnd->setScale(0.001*pixelPerMeter*dimension);

	Point centerPosition(state.getPosition());
	Point rightEndPosition(state.getPosition() + Point(destructionRange*dimension, 0));
	Point leftEndPosition(state.getPosition() - Point(destructionRange*dimension, 0));
	Point upperEndPosition(state.getPosition() + Point(0, destructionRange*dimension));
	Point lowerEndPosition(state.getPosition() - Point(0, destructionRange*dimension));

	centerPosition *= pixelPerMeter;
	rightEndPosition *= pixelPerMeter;
	leftEndPosition *= pixelPerMeter;
	upperEndPosition *= pixelPerMeter;
	lowerEndPosition *= pixelPerMeter;

	centerPosition.switchIntoQtCoordinates();
	rightEndPosition.switchIntoQtCoordinates();
	leftEndPosition.switchIntoQtCoordinates();
	upperEndPosition.switchIntoQtCoordinates();
	lowerEndPosition.switchIntoQtCoordinates();

	m_center->setPos(centerPosition.toQPoint());
	m_leftEnd->setPos(leftEndPosition.toQPoint());
	m_rightEnd->setPos(rightEndPosition.toQPoint());
	m_lowerEnd->setPos(lowerEndPosition.toQPoint());
	m_upperEnd->setPos(upperEndPosition.toQPoint());

	scene.addItem(m_center);
	scene.addItem(m_upperEnd);
	scene.addItem(m_leftEnd);
	scene.addItem(m_rightEnd);
	scene.addItem(m_lowerEnd);

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsSvgItem *item = new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"));
		Point position(state.getPosition() + Point(i, 0));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		item->setScale(0.001*pixelPerMeter*dimension);
		scene.addItem(item);
		m_middleParts.push_back(item);
	}

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsSvgItem *item = new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"));
		item->rotate(180);
		Point position(state.getPosition() - Point(i, 0));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		item->setScale(0.001*pixelPerMeter*dimension);
		scene.addItem(item);
		m_middleParts.push_back(item);
	}

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsSvgItem *item = new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"));
		Point position(state.getPosition() + Point(0, i));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		item->setScale(0.001*pixelPerMeter*dimension);
		scene.addItem(item);
		m_middleParts.push_back(item);
	}

	for (unsigned int i = 1; i < destructionRange; ++i)
	{
		QGraphicsSvgItem *item = new QGraphicsSvgItem(QString("resources/graphics/explosion_flame.svg"));
		item->rotate(90);
		Point position(state.getPosition() - Point(0, i));
		position *= pixelPerMeter;
		position.switchIntoQtCoordinates();
		item->setPos(position.toQPoint());
		item->setScale(0.001*pixelPerMeter*dimension);
		scene.addItem(item);
		m_middleParts.push_back(item);
	}
}

ExplodedBomb::~ExplodedBomb()
{
	delete m_center;
	delete m_upperEnd;
	delete m_leftEnd;
	delete m_lowerEnd;
	delete m_rightEnd;

	for (vector<QGraphicsSvgItem*>::iterator i = m_middleParts.begin(); i != m_middleParts.end(); ++i)
		delete *i;
	m_middleParts.clear();
}
