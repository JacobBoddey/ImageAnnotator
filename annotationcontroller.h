#ifndef ANNOTATIONCONTROLLER_H
#define ANNOTATIONCONTROLLER_H

#include <graphicsimage.h>
#include <image.h>

#include <QList>

class AnnotationController
{

private:

    QList<GraphicsImage*>* imageAnnotations;

public:

    AnnotationController();

    QList<GraphicsImage*>* getImageAnnotations();

    GraphicsImage* getImageAnnotations(Image* image);

    void addAnnotations(GraphicsImage* graphicsImage);

};

#endif // ANNOTATIONCONTROLLER_H
