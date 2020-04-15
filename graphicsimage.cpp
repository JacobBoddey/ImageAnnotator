#include "graphicsimage.h"

#include <iostream>

GraphicsImage::GraphicsImage(QObject* parent)
{

}

void GraphicsImage::setDrawingMode(GraphicsImage::DrawMode mode) {
    drawingMode = mode;
}

GraphicsImage::DrawMode GraphicsImage::getDrawingMode() {
    return drawingMode;
}

void GraphicsImage::mousePressEvent(QGraphicsSceneMouseEvent* event) {

    //std::cout << "Pressed at" << event->scenePos().x() << ", " << event->scenePos().y() << std::endl;

}

GraphicsImage::~GraphicsImage() {

}
