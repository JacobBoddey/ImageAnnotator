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

    GraphicsImage* getImageAnnotations(QString fName);

    void addAnnotations(GraphicsImage* graphicsImage);

    QJsonDocument toJSON();

    void removeAnnotations(GraphicsImage* gImage);

    int getNumberAnnotations();

};

#endif // ANNOTATIONCONTROLLER_H
