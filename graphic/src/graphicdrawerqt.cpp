#include "graphicdrawerqt.h"
#include "player.h"
#include <QGraphicsScene>

using namespace Graphic;
using namespace Common;

GraphicDrawerQt::GraphicDrawerQt() :
	m_scene(new QGraphicsScene()),
	m_player(new Player(*m_scene))
{
	m_scene->setSceneRect(-100, -100, 200, 200);
}

GraphicDrawerQt::~GraphicDrawerQt()
{
	delete m_scene;
	delete m_player;
}

void GraphicDrawerQt::draw(const GameState &/*gameState*/)
{
}

QGraphicsScene &GraphicDrawerQt::getScene()
{
	return *m_scene;
}