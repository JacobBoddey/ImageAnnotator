#ifndef ANNOTATIONCONTROLLER_H
#define ANNOTATIONCONTROLLER_H

#include <graphicsimage.h>
#include <image.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

    void saveAnnotations(QString fileName);

    int getNumberAnnotations();

};

#endif // ANNOTATIONCONTROLLER_H
