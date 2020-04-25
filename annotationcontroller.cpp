#include "annotationcontroller.h"

#include <iostream>

AnnotationController::AnnotationController()
{
    imageAnnotations = new QList<GraphicsImage*>();
}

void AnnotationController::addAnnotations(GraphicsImage* graphicsImage) {
    if (getImageAnnotations(graphicsImage->fileName) != NULL) {
        removeAnnotations(graphicsImage);
    }
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

GraphicsImage* AnnotationController::getImageAnnotations(QString fileName) {
    for (int i = 0 ; i < imageAnnotations->size() ; i ++) {
        if (imageAnnotations->at(i)->fileName == fileName) {
            return imageAnnotations->at(i);
        }
    }
    return NULL;
}

void AnnotationController::removeAnnotations(GraphicsImage* gImage) {
    imageAnnotations->removeOne(gImage);
}

int AnnotationController::getNumberAnnotations() {
    return imageAnnotations->size();
}

void AnnotationController::saveAnnotations(QString fileName) {

    QFile saveFile(fileName);

    QJsonObject annotationsObject;

    annotationsObject.insert("numImages", imageAnnotations->size());

    QJsonArray annotationsArray;

    for (int i = 0 ; i < imageAnnotations->size() ; i ++) {

        GraphicsImage* annotation = imageAnnotations->at(i);

        QJsonObject annotationObject;

        annotationObject.insert("imageName", annotation->fileName);
        annotationObject.insert("numShapes", annotation->getShapes().size());

        QJsonArray shapesArray;
        for (int j = 0 ; j < annotation->getShapes().size() ; j ++) {

            QGraphicsPolygonItem* shape = imageAnnotations->at(i)->getShapes().at(j);
            QJsonObject shapeObject;
            shapeObject.insert("type", "TRIANGLE");

            QJsonArray shapePoints;
            for (int k = 0 ; k < shape->polygon().size() ; k ++) {
                QJsonArray shapeVertices;
                shapeVertices.insert(0, shape->polygon().at(k).x());
                shapeVertices.insert(1, shape->polygon().at(k).y());
                shapePoints.insert(k, shapeVertices);
            }
            shapeObject.insert("vertices", shapePoints);
            shapesArray.insert(j, shapeObject);
        }

        annotationObject.insert("shapes", shapesArray);
        annotationsArray.insert(i, annotationObject);
    }

    annotationsObject.insert("annotations", annotationsArray);

    QJsonDocument jsonDocument(annotationsObject);

}
