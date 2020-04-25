#ifndef GRAPHICSIMAGE_H
#define GRAPHICSIMAGE_H

#include <QApplication>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QGraphicsLineItem>
#include <QPen>

#include <math.h>

class GraphicsImage : public QObject, public QGraphicsPixmapItem
{

public:

    enum DrawMode { SELECT, DELETE, COPY, PASTE, TRIANGLE, RECTANGLE, TRAPEZIUM, POLYGON };

    GraphicsImage(QObject* parent);

    QString fileName;

    QString filePath;

    QList<QPointF> getPoints();

    QList<QGraphicsPolygonItem*> getShapes();

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
    QList<QGraphicsPolygonItem*> shapes;
    QGraphicsLineItem* drawingLine;
    QGraphicsPolygonItem* selectedShape;

};

#endif // GRAPHICSIMAGE_H
