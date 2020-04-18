#include "graphicsimage.h"

#include <iostream>

GraphicsImage::GraphicsImage(QObject* parent)
{
    points = QList<QPointF>();
    tempLines = QList<QGraphicsLineItem*>();
    shapes = QList<QGraphicsPolygonItem*>();

    selectedShape = NULL;

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
    if (mode != SELECT && mode != DELETE) {
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

        if (selectedShape != NULL) { //A shape is already selected, check if it is still selected
            if (selectedShape->contains(event->scenePos())) {
                //Still selected, do nothing
                std::cout << "Shape is still selected" << std::endl;
                return;
            }
            else { //Shape is no longer selected, de select it
                selectedShape->setSelected(false);
                std::cout << "Deselecting shape" << std::endl;
                selectedShape = NULL;
            }
        }

        foreach (QGraphicsPolygonItem* polygon, shapes) {
            if (polygon->contains(event->scenePos())) {
                selectedShape = polygon;
                polygon->setSelected(true);
                return;
            }
        }

    }
    else if (drawingMode == DELETE) {
        foreach (QGraphicsPolygonItem* polygon, shapes) {
            if (polygon->contains(event->scenePos())) {
                shapes.removeOne(polygon);
                delete polygon;
                return;
            }
        }
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

        if (points.size() == 0 || points.size() == 1) {
            points.append(event->scenePos());
            if (points.size() == 2) {
                drawLine(points.at(0), points.at(1));
            }
        }
        else if (points.size() == 2) {
            points.append(drawingLine->line().p2());
            drawLine(points.at(points.size() - 2), points.at(points.size() - 1));
        }
        else if (points.size() == 3) {
            points.append(event->scenePos());
            drawShape(points);
        }
    }
    else if (drawingMode == TRAPEZIUM) {
        if (points.size() == 3) {
            points.append(event->scenePos());
            drawShape(points);
        }
        else {
            points.append(event->scenePos());
            if (points.size() == 2 || points.size() == 3) {
                drawLine(points.at(points.size() - 2), points.at(points.size() - 1));
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

                qreal angle = line.angle();

                qreal perpendicular = 0;
                if (angle > 270.0) {
                    perpendicular = angle - 90;
                }
                else {
                    perpendicular = angle + 90;
                }

                QLineF toCursor = QLineF();
                toCursor.setP1(points.at(1));
                toCursor.setP2(event->scenePos());
                qreal distance = toCursor.length();

                QLineF newLine = QLineF();
                newLine.setP1(points.at(1));
                newLine.setP2(event->scenePos());
                newLine.setAngle(perpendicular);

                drawingLine->setLine(newLine);

            }
            else if (points.size() == 3) {

                //Change mouse location
                points.append(event->scenePos());
                drawShape(points);
            }
        }

        else if (getDrawingMode() == TRAPEZIUM) {
            if (points.size() >= 1 && points.size() <= 3) {
                QLineF line = QLineF();
                line.setP1(getPoints().last());
                line.setP2(event->scenePos());
                drawingLine->setLine(line);
            }
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

    shape->setFlag(GraphicsItemFlag::ItemIsMovable, true);
    shape->setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    shapes.append(shape);

    points.clear();
    drawingLine->hide();
}

GraphicsImage::~GraphicsImage() {

}
