#include "graphicsimage.h"

#include <iostream>

GraphicsImage::GraphicsImage(QObject* parent)
{
    points = QList<QPointF>();
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
        if (points.size() == 1) {
            //Plot the second, then join the first and last points
            points.empty();
        }
        else {
            points.append(event->scenePos());
            if (points.size() == 2) {
                //Draw line from first to last point
            }
        }
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

void GraphicsImage::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    if (points.size() != 0) {
        //Draw line from last point to cursor
    }

}

GraphicsImage::~GraphicsImage() {

}
