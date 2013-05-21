#ifndef PLAYER_H
#define PLAYER_H

class QGraphicsScene;
class QGraphicsRectItem;

namespace Graphic
{
class Player
{
public:
	Player(QGraphicsScene &scene);
	~Player();

private:
	QGraphicsRectItem *m_item;
};
}

#endif
