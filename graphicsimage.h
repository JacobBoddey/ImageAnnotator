#ifndef GRAPHICSIMAGE_H
#define GRAPHICSIMAGE_H

#include <QApplication>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QGraphicsLineItem>
#include <QPen>

class GraphicsImage : public QObject, public QGraphicsPixmapItem
{

public:

    enum DrawMode { SELECT, TRIANGLE, RECTANGLE, TRAPEZIUM, POLYGON };

    GraphicsImage(QObject* parent);

    QList<QPointF> getPoints();

    void setDrawingMode(DrawMode mode);

    DrawMode getDrawingMode();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void hoverMoveEvent(QGraphicsSceneHoverEvent* event);

    void drawLine(QPointF from, QPointF to);

    void clearLines();

    void drawShape(QList<QPointF> points);

    ~GraphicsImage();

private:

    DrawMode drawingMode = DrawMode::SELECT;

    QList<QPointF> points;
    QList<QGraphicsLineItem*> tempLines;
    QGraphicsLineItem* drawingLine;

};

#endif // GRAPHICSIMAGE_H
