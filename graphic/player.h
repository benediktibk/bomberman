#ifndef GRAPHIC_PLAYER_H
#define GRAPHIC_PLAYER_H

class QGraphicsScene;
class QGraphicsSvgItem;

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
	Player(QGraphicsScene &scene, SvgRenderer &renderer);
	~Player();

	void update(const Common::PlayerState &state, double pixelPerMeter);

private:
	QGraphicsSvgItem *m_standing;
	QGraphicsSvgItem *m_movingLeft;
	QGraphicsSvgItem *m_movingUp;
	QGraphicsSvgItem *m_movingRight;
	QGraphicsSvgItem *m_movingDown;
};
}

#endif
