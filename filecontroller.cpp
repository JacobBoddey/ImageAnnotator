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
