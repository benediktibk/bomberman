#ifndef BOMB_H
#define BOMB_H

class QGraphicsScene;
class QGraphicsRectItem;

namespace Common
{
	class BombState;
}

namespace Graphic
{
class Bomb
{
public:
	Bomb(QGraphicsScene &scene);
	~Bomb();

	void update(const Common::BombState &state, double pixelPerMeter);

private:
	QGraphicsRectItem *m_item;
};
}

#endif
