#include "filecontroller.h"

/**
 * FileController constructor
 */

FileController::FileController()
{

}

/**
 * Save the annotations to file
 *
 * @param QString - The name of the file name to save to (full path)
 * @param QJsonDocument - The JSON document to save
 */

void FileController::saveAnnotations(QString fileName, QJsonDocument json) {

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(json.toJson());
    file.close();

}

/**
 * Get a JSON document from a file
 *
 * @param QString - The file name of the file (full path)
 * @return QJsonDocument - The JSON document from the file
 */

QJsonDocument FileController::loadAnnotations(QString fileName) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    return jsonDoc;

}
