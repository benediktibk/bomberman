#ifndef GRAPHICDRAWERQT_H
#define GRAPHICDRAWERQT_H

#include "graphicdrawer.h"

class QGraphicsScene;

namespace Graphic
{
class Player;

class GraphicDrawerQt :
		public Common::GraphicDrawer
{
public:
	GraphicDrawerQt();
	virtual ~GraphicDrawerQt();

	virtual void draw(const Common::GameState &gameState);
	QGraphicsScene& getScene();

private:
	QGraphicsScene *m_scene;
	Player *m_player;
};
}

#endif
