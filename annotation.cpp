#include "annotation.h"

/**
 * Annotation constructor
 */

Annotation::Annotation()
{

}

/**
 * Get the image from the annotation
 *
 * @return Image* - Pointer to the image this annotations belongs to
 */

Image* Annotation::getImage() {
    return image;
}

/**
 * Set the parent image
 *
 * @param Image* - Pointer to the image
 */

void Annotation::setImage(Image* im) {
    image = im;
}

/**
 * Get the shapes from this annotation
 *
 * @return QList<QGraphicsPolygonItem* - A list of shapes
 */

QList<QGraphicsPolygonItem*> Annotation::getShapes() {
    return shapes;
}

/**
 * Set the shapes list
 *
 * @param QList<QGraphicsPolygonItem* - Pointer to the list of shapes
 */

void Annotation::setShapes(QList<QGraphicsPolygonItem*> sh) {
    shapes = sh;
}


