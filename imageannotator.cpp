#include "imageannotator.h"
#include "ui_imageannotator.h"

#include <annotationcontroller.h>
#include <classlabelcontroller.h>
#include <imagecontroller.h>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <graphicsimage.h>

#include <thread>
#include <iostream>

AnnotationController annotationController;
ClassLabelController classLabelController;
ImageController imageController;

void AutoSave() {
    while (true) {
        std::cout << "Ran auto save" << std::endl;
        std::chrono::seconds sec(5);
        std::this_thread::sleep_for(sec);
    }
}

ImageAnnotator::ImageAnnotator(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImageAnnotator)
{
    ui->setupUi(this);

    classLabelController = ClassLabelController();
    imageController = ImageController();

    //std::thread autoSaveThread(AutoSave);

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

void ImageAnnotator::on_sortImageReset_clicked()
{
    ui->sortImageType->setCurrentIndex(0);
    ui->sortImageOrder->setCurrentIndex(0);
    imageController.displayImages(ui->imageTableView, imageController.sortByName("Ascending"));
}

void ImageAnnotator::on_sortImageButton_clicked()
{
    QString sortWhat = ui->sortImageType->currentText();
    QString sortOrder = ui->sortImageOrder->currentText();

    if (sortWhat == "Name") {
        imageController.displayImages(ui->imageTableView, imageController.sortByName(sortOrder));
    }
    else {
        imageController.displayImages(ui->imageTableView, imageController.sortByDate(sortOrder));
    }

}

void ImageAnnotator::on_imageTableView_cellClicked(int row, int column)
{
    column = 0;

    QString name = ui->imageTableView->item(row, column)->text();

    Image* image = imageController.getImage(name);

    QImage qImage(image->getPath() + "/" + image->getName());

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap = QPixmap::fromImage(qImage);
    graphicsImage = new GraphicsImage(new QObject());
    graphicsImage->setPixmap(pixmap);
    graphicsImage->setAcceptHoverEvents(true);
    scene->addItem(graphicsImage);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setInteractive(true);

}

void ImageAnnotator::on_zoomInButton_clicked()
{
    if (ui->graphicsView->transform().m11() < 2.0) {
        ui->graphicsView->scale(1.25, 1.25);
    }
}

void ImageAnnotator::on_zoomOutButton_clicked()
{
    if (ui->graphicsView->transform().m11() > 0.05) {
        ui->graphicsView->scale(0.75, 0.75);
    }
}

void ImageAnnotator::on_triangleButton_clicked()
{
    if (graphicsImage != NULL) {
        graphicsImage->setDrawingMode(GraphicsImage::DrawMode::TRIANGLE);
    }
}

void ImageAnnotator::on_squareButton_clicked()
{
    if (graphicsImage != NULL) {
        graphicsImage->setDrawingMode(GraphicsImage::DrawMode::RECTANGLE);
    }
}

void ImageAnnotator::on_trapeziumButton_clicked()
{
    if (graphicsImage != NULL) {
        graphicsImage->setDrawingMode(GraphicsImage::DrawMode::TRAPEZIUM);
    }
}

void ImageAnnotator::on_polygonButton_clicked()
{
    if (graphicsImage != NULL) {
        graphicsImage->setDrawingMode(GraphicsImage::DrawMode::POLYGON);
    }
}

void ImageAnnotator::on_selectCursor_clicked()
{
    if (graphicsImage != NULL) {
        graphicsImage->setDrawingMode(GraphicsImage::DrawMode::SELECT);
    }
}

void ImageAnnotator::on_deleteButton_clicked()
{
    if (graphicsImage != NULL) {
        graphicsImage->setDrawingMode(GraphicsImage::DrawMode::DELETE);
    }
}

void ImageAnnotator::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open Annotations", QDir::currentPath(), "Annotations (*.annotations)");
    QFile annotationsFile(fileName);

}

void ImageAnnotator::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Annotations", QDir::currentPath(), ".annotations");
}
