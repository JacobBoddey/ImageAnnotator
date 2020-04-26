#include <graphicsshape.h>

#include <iostream>

/**
 * GraphicsShape constructor
 *
 * @param QGraphicsItem* - The parent widget
 */

GraphicsShape::GraphicsShape(QGraphicsItem *parent) : QGraphicsPolygonItem(parent)
{

}

/**
 * Mouse Press Event
 *
 * @param QGraphicsSceneMouseEvent - The event object
 */

void GraphicsShape::mousePressEvent(QGraphicsSceneMouseEvent* event) {

}

/**
 * GraphicsShape deconstructor
 */

GraphicsShape::~GraphicsShape() {

}
