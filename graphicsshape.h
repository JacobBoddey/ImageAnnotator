#ifndef GRAPHICSSHAPE_H
#define GRAPHICSSHAPE_H

#include <graphicsimage.h>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class GraphicsShape : public QGraphicsPolygonItem
{

public:

    GraphicsShape(QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    ~GraphicsShape();

private:

};

#endif // GRAPHICSSHAPE_H
