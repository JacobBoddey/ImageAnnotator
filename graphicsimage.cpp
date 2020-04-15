#include "graphicsimage.h"

#include <iostream>

GraphicsImage::GraphicsImage(QObject* parent)
{
    points = QList<QPointF>();
    tempLines = QList<QGraphicsLineItem*>();

    drawingLine = new QGraphicsLineItem(this);
    QPen pen = QPen();
    pen.setWidth(2);
    drawingLine->setPen(pen);
    drawingLine->hide();

}

QList<QPointF> GraphicsImage::getPoints() {
    return points;
}

void GraphicsImage::setDrawingMode(GraphicsImage::DrawMode mode) {
    drawingMode = mode;
    if (mode != SELECT) {
        QApplication::setOverrideCursor(Qt::CrossCursor);
    }
    else {
        QApplication::restoreOverrideCursor();
    }
}

GraphicsImage::DrawMode GraphicsImage::getDrawingMode() {
    return drawingMode;
}

void GraphicsImage::mousePressEvent(QGraphicsSceneMouseEvent* event) {

    if (drawingMode == SELECT) {
        //Check for point within radius
        //If point is found, drag point
    }
    else if (drawingMode == TRIANGLE) {
        points.append(event->scenePos());
        if (points.size() == 2) {
             drawLine(points.at(0), points.at(1));
        }
        else if (points.size() == 3) {
            drawShape(points);
        }
        return;
    }
    else if (drawingMode == RECTANGLE) {
        if (points.size() == 2) {
            //Append last point, but ensuring side is parallel
            //Complete rectangle by plotting from first to second point, second to third, and first to a calculated point using first and third
            points.empty();
        }
        else {
            points.append(event->scenePos());
            if (points.size() == 2) {
                //Draw line from first to second point
            }
        }
    }
    else if (drawingMode == TRAPEZIUM) {
        if (points.size() == 3) {

        }
        else {
            points.append(event->scenePos());
            if (points.size() == 2 || points.size() == 3) {
                //Draw line from previous point to last point
            }
        }
    }
    else if (drawingMode == POLYGON) {
        points.append(event->scenePos());
        if (points.size() == 7) {
            //Complete octagon by plotting from last to first point
            points.empty();
        }
        else {
            if (points.size() > 1) {
                //Draw line from previous to last point
            }
        }
    }
    //std::cout << "Pressed at" << event->scenePos().x() << ", " << event->scenePos().y() << std::endl;

}

void GraphicsImage::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {

    if (!points.empty()) {
        drawingLine->show();
        if (getDrawingMode() == TRIANGLE) {
            QLineF line = QLineF();
            line.setP1(getPoints().last());
            line.setP2(event->scenePos());
            drawingLine->setLine(line);
        }
    }

}

void GraphicsImage::drawLine(QPointF from, QPointF to) {
    QGraphicsLineItem* line = new QGraphicsLineItem(this);
    QLineF lineF = QLineF(from, to);
    QPen pen = QPen();
    pen.setWidth(2);
    line->setPen(pen);
    line->setLine(lineF);
    tempLines.append(line);
}

void GraphicsImage::clearLines() {
    for (int i = 0; i < tempLines.size();i++) {
        QGraphicsLineItem* item = tempLines.at(i);
        delete item;
    }
    tempLines.clear();
}

void GraphicsImage::drawShape(QList<QPointF> p) {
    clearLines();
    points.clear();
    drawingLine->hide();
}

GraphicsImage::~GraphicsImage() {

}
