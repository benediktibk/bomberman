#ifndef GRAPHICDRAWERQT_H
#define GRAPHICDRAWERQT_H

#include "graphicdrawer.h"

class QGraphicsScene;
class QGraphicsView;

namespace Graphic
{
class Player;

class GraphicDrawerQt :
		public Common::GraphicDrawer
{
public:
	GraphicDrawerQt(QGraphicsView &view);
	virtual ~GraphicDrawerQt();

	virtual void draw(const Common::GameState &gameState);
	QGraphicsScene& getScene();

private:
	QGraphicsView &m_view;
	QGraphicsScene *m_scene;
	Player *m_player;
};
}

#endif
