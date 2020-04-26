#include "annotationcontroller.h"

#include <iostream>

/**
 * AnnotationController constructor
 *
 * Initialises imageAnnotations to a new empty QList of GraphicsImage pointers
 */

AnnotationController::AnnotationController()
{
    imageAnnotations = new QList<GraphicsImage*>();
}

/**
 * Add an annotation to the list
 *
 * @param GraphicsImage* - The GraphicsImage pointer to add
 */

void AnnotationController::addAnnotations(GraphicsImage* graphicsImage) {
    if (getImageAnnotations(graphicsImage->fileName) != NULL) {
        removeAnnotations(graphicsImage);
    }
    imageAnnotations->append(graphicsImage);
}

/**
 * Get a GraphicsImage pointer
 *
 * @param Image* - Pointer to the image to search by
 */

GraphicsImage* AnnotationController::getImageAnnotations(Image* image) {

    for (int i = 0 ; i < imageAnnotations->size() ; i ++) {
        if (imageAnnotations->at(i)->fileName == image->getName()) {
            return imageAnnotations->at(i);
        }
    }
    return NULL;
}

/**
 * Get a GraphicsImage pointer
 *
 * @param QString - File name of the image belonging to the Graphics Image
 * @return GraphicsImage* - A pointer to the Graphics Image with the matching name
 */

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

/**
 * Get the number of annotations in the list of annotations for this Graphics Image
 *
 * @return int - The number of annotations in the list
 */

int AnnotationController::getNumberAnnotations() {
    return imageAnnotations->size();
}

/**
 * Get the JSON format of the annotations
 *
 * @return QJsonDocument - The JSON output
 */

QJsonDocument AnnotationController::toJSON() {

    QJsonObject annotationsObject;

    annotationsObject.insert("numImages", imageAnnotations->size());
    annotationsObject.insert("imagesPath", imageAnnotations->at(0)->filePath);

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
    return jsonDocument;

}
