#include "graphicsimage.h"

#include <iostream>

GraphicsImage::GraphicsImage(QObject* parent)
{
    points = QList<QPointF>();
    tempLines = QList<QGraphicsLineItem*>();
    shapes = QList<QGraphicsPolygonItem*>();

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
    }
    else if (drawingMode == RECTANGLE) {
        points.append(event->scenePos());
        if (points.size() == 2 || points.size() == 3) {
            drawLine(points.at(points.size() - 2), points.at(points.size() - 1));
        }
        else if (points.size() == 4) {
            drawShape(points);
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

        if (points.size() > 2) {

            QPointF firstPoint = getPoints().first();
            QLineF distanceLine = QLineF(firstPoint, event->scenePos());

            if (distanceLine.length() < 10) {
                points.append(QPointF(firstPoint.x(), firstPoint.y()));
                drawShape(points);
                return;
            }

        }

        points.append(event->scenePos());

        if (points.size() == 8) {
            drawShape(points);
        }
        else {
            if (points.size() > 1) {
                drawLine(points.at(points.size() - 2), points.at(points.size() - 1));
            }
        }
    }

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
        else if (getDrawingMode() == RECTANGLE) {
            if (points.size() == 1) {
                QLineF line = QLineF();
                line.setP1(getPoints().last());
                line.setP2(event->scenePos());
                drawingLine->setLine(line);
            }
            else if (points.size() == 2) {

                QLineF line = QLineF();
                line.setP1(points.at(0));
                line.setP2(points.at(1));

                qreal perpendicular;
                if (line.angle() > 270) {
                    perpendicular = line.angle() - 90;
                }
                else {
                    perpendicular = line.angle() + 90;
                }
                perpendicular = (perpendicular * (atan(1)*4)) / 180;

                QLineF newLine = QLineF();
                newLine.setP1(points.at(1));
                qreal x = points.at(1).x();
                qreal y = points.at(1).y();

                QLineF distanceCal = QLineF();
                distanceCal.setP1(points.at(1));
                distanceCal.setP2(event->scenePos());
                int distance = distanceCal.length();

                QPointF perpendicularPoint = QPointF();
                perpendicularPoint.setX(x + (distance * cos(perpendicular)));
                perpendicularPoint.setY(y + (distance * sin(perpendicular)));
                newLine.setP2(perpendicularPoint);

                drawingLine->setLine(newLine);

            }
        }

        else if (getDrawingMode() == TRAPEZIUM) {

        }
        else if (getDrawingMode() == POLYGON) {
            if (points.size() > 0 && points.size() < 8) {
                QLineF line = QLineF();

                if (points.size() > 2) {

                    QPointF firstPoint = getPoints().first();
                    QLineF distanceLine = QLineF(firstPoint, event->scenePos());

                    if (distanceLine.length() < 10) {
                        line.setP1(getPoints().last());
                        line.setP2(firstPoint);
                        drawingLine->setLine(line);
                        return;
                    }

                }
                line.setP1(getPoints().last());
                line.setP2(event->scenePos());
                drawingLine->setLine(line);
            }

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

    QPolygonF polygon = QPolygonF();
    for (int i = 0;i<p.size();i++) {
        polygon.append(p.at(i));
    }
    QGraphicsPolygonItem* shape = new QGraphicsPolygonItem(this);
    QPen pen = QPen();
    pen.setWidth(2);
    shape->setPen(pen);
    shape->setPolygon(polygon);
    shapes.append(shape);

    points.clear();
    drawingLine->hide();
}

GraphicsImage::~GraphicsImage() {

}
