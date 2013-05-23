#ifndef WALL_H
#define WALL_H

class QGraphicsScene;
class QGraphicsRectItem;

namespace Common
{
	class WallState;
}

namespace Graphic
{
class Wall
{
public:
	Wall(QGraphicsScene &scene);
	~Wall();

	void update(const Common::WallState &state);

private:
	QGraphicsRectItem *m_item;
};
}

#endif
