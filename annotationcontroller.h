#ifndef ANNOTATIONCONTROLLER_H
#define ANNOTATIONCONTROLLER_H

#include <graphicsimage.h>

#include <QList>

class AnnotationController
{

private:

    QList<GraphicsImage*>* imageAnnotations;

public:

    AnnotationController();

    QList<GraphicsImage*>* getImageAnnotations();

};

#endif // ANNOTATIONCONTROLLER_H
