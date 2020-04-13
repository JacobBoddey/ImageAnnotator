#include "imageannotator.h"
#include "ui_imageannotator.h"

#include <classlabel.h>
#include <classlabelcontroller.h>

#include <QFileDialog>
#include <QTextStream>
#include <iostream>

ClassLabelController classLabelController;

ImageAnnotator::ImageAnnotator(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImageAnnotator)
{
    ui->setupUi(this);

    classLabelController = ClassLabelController();

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

    QString classes = "";
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
