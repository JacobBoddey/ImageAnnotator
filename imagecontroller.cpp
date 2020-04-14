#include "imagecontroller.h"

ImageController::ImageController()
{
    images = QList<Image*>();
}

QList<Image*>* ImageController::getImages() {
    return &images;
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

    widget->clearContents();

    for (int i = 0 ; i < im->size() ; i ++) {
        Image* image = images.at(i);
        QTableWidgetItem* fileName = new QTableWidgetItem(image->getName());
        fileName->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* dateModified = new QTableWidgetItem(image->getDateModified().toString("dd/MM/yy"));
        dateModified->setTextAlignment(Qt::AlignCenter);

        widget->insertRow(widget->rowCount());

        widget->setItem(widget->rowCount() - 1, 0, fileName);
        widget->setItem(widget->rowCount() - 1, 1, dateModified);

       widget->resizeRowToContents(widget->rowCount() - 1);

    }

}
