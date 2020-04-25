#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <qstring.h>
#include <QJsonDocument>
#include <QFile>

class FileController
{

private:

public:

    FileController();

    void saveAnnotations(QString fileName, QJsonDocument json);

};

#endif // FILECONTROLLER_H
