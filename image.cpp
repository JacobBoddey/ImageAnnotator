#include "image.h"

Image::Image(QFile* f, QFileInfo* info)
{
    imageFile = f;
    name = info->fileName();
    path = info->path();
    dateModified = info->lastModified();
}

QString Image::getPath() {
    return path;
}

QString Image::getName() {
    return name;
}

QDateTime Image::getDateModified() {
    return dateModified;
}
