#include "annotation.h"

Annotation::Annotation()
{

}

Image* Annotation::getImage() {
    return image;
}

void Annotation::setImage(Image* im) {
    image = im;
}

QList<QGraphicsPolygonItem*> Annotation::getShapes() {
    return shapes;
}

void Annotation::setShapes(QList<QGraphicsPolygonItem*> sh) {
    shapes = sh;
}


