#ifndef PLAYER_H
#define PLAYER_H

class QGraphicsScene;
class QGraphicsRectItem;

namespace Common
{
	class PlayerState;
}

namespace Graphic
{
class Player
{
public:
	Player(QGraphicsScene &scene);
	~Player();

	void update(const Common::PlayerState &state);

private:
	QGraphicsRectItem *m_item;
};
}

#endif
