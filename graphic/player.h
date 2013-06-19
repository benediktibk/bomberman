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
	Player(QGraphicsScene &scene);
	Player(QGraphicsScene &scene, SvgRenderer &renderer);
	~Player();

	void update(const Common::PlayerState &state, double pixelPerMeter);

private:
	QGraphicsSvgItem *m_svgItem;
};
}

#endif
