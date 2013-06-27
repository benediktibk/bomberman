#ifndef GRAPHIC_PLAYER_H
#define GRAPHIC_PLAYER_H

class QGraphicsScene;
class QGraphicsItem;

namespace Common
{
	class PlayerState;
}

namespace Graphic
{
class SvgRenderer;

class Player
{
public:
	Player(QGraphicsScene &scene, SvgRenderer &renderer, const Common::PlayerState &state);
	~Player();

	void update(const Common::PlayerState &state, double pixelPerMeter);

private:
	QGraphicsItem *m_standing;
	QGraphicsItem *m_movingLeft;
	QGraphicsItem *m_movingUp;
	QGraphicsItem *m_movingRight;
	QGraphicsItem *m_movingDown;
};
}

#endif
