#include "imagecontroller.h"

#include <iostream>

/**
 * Initialising the Image Controller
 *
 * Sets images to new QList of type Image pointer
 */

ImageController::ImageController()
{
    images = QList<Image*>();
}

/**
 * Retrieves the list of images
 *
 * @return QList<Image*>* - pointer list of image pointers
 */

QList<Image*>* ImageController::getImages() {
    return &images;
}


/**
 * Retrieves the list of images
 *
 * @param name - The file name e.g picture.png
 * @return Image* - pointer to the image with the matching file name
 */

Image* ImageController::getImage(QString name) {
    for (int i = 0 ; i < images.size() ; i++) {
        if (images.at(i)->getName() == name) {
            return images.at(i);
        }
    }
}


/**
 * Loads images from a directory
 *
 * @param QDir - the directory in which to load the images from
 */

void ImageController::loadImages(QDir dir) {

    QFileInfoList imagesList = dir.entryInfoList(QStringList() << "*.jpg" << "*.png", QDir::Files);

    images.clear();

    foreach (QFileInfo fileInfo, imagesList) {
        QFile file(fileInfo.path());
        Image* image = new Image(&file, &fileInfo);
        images.append(image);
    }

}

/**
 * Adds an image to the list of images
 *
 * @param Image* - the pointer to the image to add
 */

void ImageController::addImage(Image* i) {
    images.append(i);
}

/**
 * Removes an image from the list
 *
 * @param Image* - pointer to the image to remove
 */

void ImageController::removeImage(Image* i) {
    images.removeOne(i);
}

/**
 * Displays a list of images in the table view
 *
 * @param QTableWidget* - pointer to the table widget which contains the image listings
 * @param QList<Image*>* - pointer to the list of images to display within the widget
 */

void ImageController::displayImages(QTableWidget* widget, QList<Image*>* im) {

    for (int i = widget->rowCount() ; i >= 0 ; i--) {
        widget->removeRow(i);
    }

    for (int i = 0 ; i < im->size() ; i ++) {
        Image* image = images.at(i);
        QTableWidgetItem* fileName = new QTableWidgetItem(image->getName());
        fileName->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* dateModified = new QTableWidgetItem(image->getDateModified().toString("dd/MM/yy"));
        dateModified->setTextAlignment(Qt::AlignCenter);

        widget->insertRow(i);

        widget->setItem(i, 0, fileName);
        widget->setItem(i, 1, dateModified);

        widget->resizeRowToContents(i);

    }

}

/**
 * Returns the images with names that match the search term
 *
 * @param QString - the search term
 */

QList<Image*>* ImageController::searchImages(QString term) {
    return getImages();
}

/**
 * Sorts the images by their name
 *
 * @param QString - Either "Ascending" or "Descending"
 * @return QList<Image*>* - The sorted list of images
 */

QList<Image*>* ImageController::sortByName(QString sortType) {

    for (int i = 0; i < getImages()->size() - 1; i++) {
        for (int j = 0; j < getImages()->size() - i - 1; j++) {
            if (sortType == "Descending") {
                if (getImages()->at(j)->getName() < getImages()->at(j+1)->getName()) {
                    getImages()->swap(j, j+1);
                }
            }
            else {
                if (getImages()->at(j)->getName() > getImages()->at(j+1)->getName()) {
                    getImages()->swap(j, j+1);
                }
            }
        }
    }

    return getImages();
}

/**
 * Sorts the images by the date they were last modified
 *
 * @param QString - Either "Ascending" or "Descending"
 * @return QList<Image*>* - The sorted list of images
 */

QList<Image*>* ImageController::sortByDate(QString sortType) {

    for (int i = 0; i < getImages()->size() - 1; i++) {
        for (int j = 0; j < getImages()->size() - i - 1; j++) {
            if (sortType == "Descending") {
                if (getImages()->at(j)->getDateModified() < getImages()->at(j+1)->getDateModified()) {
                    getImages()->swap(j, j+1);
                }
            }
            else {
                if (getImages()->at(j)->getDateModified() > getImages()->at(j+1)->getDateModified()) {
                    getImages()->swap(j, j+1);
                }
            }
        }
    }

    return getImages();
}
