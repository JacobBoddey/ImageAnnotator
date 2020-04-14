#include "imagecontroller.h"

#include <iostream>

ImageController::ImageController()
{
    images = QList<Image*>();
}

QList<Image*>* ImageController::getImages() {
    return &images;
}

Image* ImageController::getImage(QString name) {
    for (int i = 0 ; i < images.size() ; i++) {
        if (images.at(i)->getName() == name) {
            return images.at(i);
        }
    }
}

void ImageController::loadImages(QDir dir) {

    QFileInfoList imagesList = dir.entryInfoList(QStringList() << "*.jpg" << "*.png", QDir::Files);

    images.clear();

    foreach (QFileInfo fileInfo, imagesList) {
        QFile file(fileInfo.path());
        Image* image = new Image(&file, &fileInfo);
        images.append(image);
    }

}

void ImageController::addImage(Image* i) {
    images.append(i);
}

void ImageController::removeImage(Image* i) {
    images.removeOne(i);
}

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
