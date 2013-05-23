#include "graphicdrawerqt.h"
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace Graphic;
using namespace Common;

GraphicDrawerQt::GraphicDrawerQt(QGraphicsView &view) :
	m_view(view),
	m_scene(new QGraphicsScene()),
	m_player(new Player(*m_scene))
{
	m_scene->setSceneRect(-100, -100, 200, 200);
	m_view.setScene(m_scene);
}

GraphicDrawerQt::~GraphicDrawerQt()
{
	delete m_scene;
	delete m_player;
}

void GraphicDrawerQt::draw(const GameState &gameState)
{
	PlayerState playerState = gameState.getPlayerState();
	m_player->update(playerState);

	m_view.setBackgroundBrush(QBrush(QColor(255, 255, 255)));
}

QGraphicsScene &GraphicDrawerQt::getScene()
{
	return *m_scene;
}