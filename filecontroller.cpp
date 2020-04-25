#include "filecontroller.h"

FileController::FileController()
{

}

void FileController::saveAnnotations(QString fileName, QJsonDocument json) {

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(json.toJson());
    file.close();

}

QJsonDocument FileController::loadAnnotations(QString fileName) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    return jsonDoc;

}
