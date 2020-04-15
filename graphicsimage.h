#ifndef GRAPHICSIMAGE_H
#define GRAPHICSIMAGE_H

#include <QApplication>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class GraphicsImage : public QObject, public QGraphicsPixmapItem
{

public:

    enum DrawMode { SELECT, TRIANGLE, RECTANGLE, TRAPEZIUM, POLYGON };

    GraphicsImage(QObject* parent);

    void setDrawingMode(DrawMode mode);

    DrawMode getDrawingMode();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    ~GraphicsImage();

private:

    DrawMode drawingMode = DrawMode::SELECT;

    QList<QPointF> points;
    QList<QLine> tempLines;

};

#endif // GRAPHICSIMAGE_H
