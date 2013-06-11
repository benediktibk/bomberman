#ifndef GRAPHIC_CELLBACKGROUND_H
#define GRAPHIC_CELLBACKGROUND_H

class QGraphicsScene;
class QGraphicsSvgItem;

namespace Graphic {
    class Point;
}

namespace Graphic
{
    class CellBackground
    {
    public:
        CellBackground(QGraphicsScene &scene);
        ~CellBackground();

        void update(const Graphic::Point &point, double pixelPerMeter);

    private:
        QGraphicsSvgItem *m_svgItem;
    };
}

#endif
