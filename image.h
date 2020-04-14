#ifndef IMAGE_H
#define IMAGE_H

#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDateTime>

class Image
{

private:

    QFile* imageFile;
    QString path;
    QString name;
    QDateTime dateModified;

public:

    Image(QFile* file, QFileInfo* info);

    QFile* getFile();
    QString getPath();
    QString getName();
    QDateTime getDateModified();

};

#endif // IMAGE_H
