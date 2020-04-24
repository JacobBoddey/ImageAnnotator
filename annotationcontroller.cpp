#include "annotationcontroller.h"

AnnotationController::AnnotationController()
{
    imageAnnotations = new QList<GraphicsImage*>();
}

void AnnotationController::addAnnotations(GraphicsImage* graphicsImage) {
    imageAnnotations->append(graphicsImage);
}

GraphicsImage* AnnotationController::getImageAnnotations(Image* image) {

    return NULL;
}
