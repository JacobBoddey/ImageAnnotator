#include "annotationcontroller.h"

AnnotationController::AnnotationController()
{
    imageAnnotations = new QList<GraphicsImage*>();
}

void AnnotationController::addAnnotations(GraphicsImage* graphicsImage) {
    imageAnnotations->append(graphicsImage);
}

GraphicsImage* AnnotationController::getImageAnnotations(Image* image) {

    for (int i = 0 ; i < imageAnnotations->size() ; i ++) {
        if (imageAnnotations->at(i)->fileName == image->getName()) {
            return imageAnnotations->at(i);
        }
    }
    return NULL;
}
