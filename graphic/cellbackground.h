#ifndef GRAPHIC_CELLBACKGROUND_H
#define GRAPHIC_CELLBACKGROUND_H

#include "common/point.h"

class QGraphicsScene;
class QGraphicsSvgItem;


namespace Graphic
{
    class CellBackground
    {
    public:
        CellBackground(QGraphicsScene &scene);
        CellBackground(QGraphicsScene &scene, const Common::Point &position, double pixelPerMeter);
        ~CellBackground();

        void update(const Common::Point &position, double pixelPerMeter);

    private:
        void updateInternal(const Common::Point &position, double width, double height, double pixelPerMeter);
        QGraphicsSvgItem *m_svgItem;
    };
}

#endif
