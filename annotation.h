#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <image.h>

#include <QGraphicsPolygonItem>

class Annotation
{

private:

    Image* image;
    QList<QGraphicsPolygonItem*> shapes;

public:

    Annotation();

    Image* getImage();
    void setImage(Image* image);
    QList<QGraphicsPolygonItem*> getShapes();
    void setShapes(QList<QGraphicsPolygonItem*> s);

};

#endif // ANNOTATION_H
