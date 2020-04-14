#include "imageannotator.h"
#include "ui_imageannotator.h"

#include <classlabelcontroller.h>

#include <imagecontroller.h>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>

ClassLabelController classLabelController;
ImageController imageController;

ImageAnnotator::ImageAnnotator(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImageAnnotator)
{
    ui->setupUi(this);

    classLabelController = ClassLabelController();
    imageController = ImageController();

}

ImageAnnotator::~ImageAnnotator()
{
    delete ui;
}


void ImageAnnotator::on_browseClassButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open Classes", QDir::currentPath(), "Classes (*.names)");

    if (fileName.isEmpty()) {
        return;
    }

    classLabelController.openClassesFile = fileName;
    ui->actionSaveClasses->setEnabled(true);

    QFile classesFile(fileName);
    classesFile.open(QIODevice::ReadOnly);

    QTextStream in(&classesFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ClassLabel label = ClassLabel(line);
        classLabelController.addClassLabel(label);
    }
    classLabelController.updateClassesList(ui->classList);

}

void ImageAnnotator::on_removeClassButton_clicked()
{
    int row = ui->classList->currentRow();
    QString text = ui->classList->item(row)->text();
    ClassLabel label = classLabelController.getClassLabel(text);
    classLabelController.removeClassLabel(label);
    classLabelController.updateClassesList(ui->classList);
}

void ImageAnnotator::on_classSortType_currentTextChanged(const QString &sortType)
{
    if (sortType == "Ascending" || sortType == "Descending") {
        classLabelController.updateClassesList(ui->classList, sortType);
    }
    else {
        classLabelController.updateClassesList(ui->classList);
    }
}

void ImageAnnotator::on_actionSaveClasses_triggered()
{
    if (classLabelController.openClassesFile == nullptr) {
        //Should not have reached here
        return;
    }

    QFile classesFile(classLabelController.openClassesFile);
    if (!classesFile.exists()) {
        //Been deleted since opened
        QMessageBox messageBox;
        messageBox.critical(0,"Error","The classes file that you have loaded into Image Annotator no longer exists");
        messageBox.setFixedSize(500,200);
        ui->actionSaveClasses->setEnabled(false);
        return;
    }

    classesFile.open(QIODevice::WriteOnly);

}

void ImageAnnotator::on_browseImageButton_clicked()
{
    QDir imagesDirectory = QFileDialog::getExistingDirectory(this, "Open images folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
    QString imagesDirectoryPath = imagesDirectory.path();

    imageController.loadImages(imagesDirectory);
    imageController.displayImages(ui->imageTableView, imageController.getImages());

}
