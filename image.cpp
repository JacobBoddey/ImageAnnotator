#include "image.h"

#include <iostream>

/**
 * Image constructor
 *
 * @param QFile* - Pointer to the file that represents the image
 * @param QFileInfo* - Info from the file
 */

Image::Image(QFile* f, QFileInfo* info)
{
    imageFile = f;
    name = info->fileName();
    path = info->path();
    dateModified = info->lastModified();

}

/**
 * Get the path to the image
 *
 * @return QString - The path of the image
 */

QString Image::getPath() {
    return path;
}

/**
 * Retrieve the name of the image
 *
 * @return QString - The name of the image
 */

QString Image::getName() {
    return name;
}

/**
 * Retrieve the date the file was last modified
 *
 * @return QDateTime - The date that the image was last modified
 */

QDateTime Image::getDateModified() {
    return dateModified;
}
