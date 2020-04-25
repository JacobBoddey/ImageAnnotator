#include "imageannotator.h"
#include "ui_imageannotator.h"

AnnotationController annotationController;
ClassLabelController classLabelController;
ImageController imageController;
FileController fileController;

ImageAnnotator::ImageAnnotator(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImageAnnotator)
{
    ui->setupUi(this);

    classLabelController = ClassLabelController();
    imageController = ImageController();
    annotationController = AnnotationController();
    fileController = FileController();

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

    if (ui->classList->selectedItems().size() > 0) {
        int row = ui->classList->currentRow();
        std::cout << "1" << std::endl;
        QString text = ui->classList->item(row)->text();
        std::cout << "2" << std::endl;
        ClassLabel label = classLabelController.getClassLabel(text);
        std::cout << "3" << std::endl;
        classLabelController.removeClassLabel(label);
        std::cout << "4" << std::endl;
        QString sortType = ui->classSortType->currentText();
        std::cout << "5" << std::endl;
        classLabelController.updateClassesList(ui->classList, sortType);
    }
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

    if (graphicsImage != nullptr && graphicsImage->getShapes().size() != 0) {
        annotationController.addAnnotations(graphicsImage);
    }

    column = 0;

    QString name = ui->imageTableView->item(row, column)->text();

    Image* image = imageController.getImage(name);

    QImage qImage(image->getPath() + "/" + image->getName());
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap = QPixmap::fromImage(qImage);


    if (!annotationController.getImageAnnotations(image)) {

        graphicsImage = new GraphicsImage(new QObject());
        graphicsImage->setPixmap(pixmap);
        graphicsImage->fileName = name;
        graphicsImage->filePath = image->getPath();
        graphicsImage->setAcceptHoverEvents(true);

    }
    else {
        graphicsImage = annotationController.getImageAnnotations(image);
    }

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
    QJsonDocument jsonDocument = fileController.loadAnnotations(fileName);

    QJsonObject jsonObject = jsonDocument.object();
    QDir imagesPath(jsonObject["imagesPath"].toString());
    imageController.loadImages(imagesPath);
    imageController.displayImages(ui->imageTableView, imageController.getImages());

    QJsonArray annotationObjects = jsonObject["annotations"].toArray();
    for (int i = 0 ; i < annotationObjects.size() ; i ++) {

        QJsonObject annotationObject = annotationObjects.at(i).toObject();
        QString imageName = annotationObject["imageName"].toString();

        GraphicsImage* graphicsImage = new GraphicsImage(new QObject());

        Image* image = imageController.getImage(imageName);

        QImage qImage(image->getPath() + "/" + image->getName());
        QGraphicsScene* scene = new QGraphicsScene();
        QPixmap pixmap = QPixmap::fromImage(qImage);

        graphicsImage->setPixmap(pixmap);
        graphicsImage->fileName = imageName;
        graphicsImage->filePath = image->getPath();
        graphicsImage->setAcceptHoverEvents(true);

        QJsonArray shapesArray = annotationObject["shapes"].toArray();
        for (int j = 0 ; j < shapesArray.size() ; j ++) {

            QList<QPointF> points;
            QJsonObject shapeObject = shapesArray.at(j).toObject();

            QJsonArray shapeVertices = shapeObject["vertices"].toArray();
            for (int k = 0 ; k < shapeVertices.size() ; k ++) {
                int x = shapeVertices.at(k).toArray()[0].toInt();
                int y = shapeVertices.at(k).toArray()[1].toInt();
                points.append(QPointF(x, y));
            }

            graphicsImage->drawShape(points);

        }

        scene->addItem(graphicsImage);

        ui->graphicsView->setScene(scene);
        ui->graphicsView->setMouseTracking(true);
        ui->graphicsView->setInteractive(true);

        annotationController.addAnnotations(graphicsImage);

    }

}

void ImageAnnotator::on_actionSave_As_triggered()
{

    if (graphicsImage != NULL && graphicsImage->getShapes().size() > 0) {
        annotationController.addAnnotations(graphicsImage);
    }

    if (annotationController.getNumberAnnotations() == 0) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is nothing to save");
        messageBox.setFixedSize(500,200);
        ui->actionSaveClasses->setEnabled(false);
        return;
    }

    QFileDialog* fileDialog = new QFileDialog();
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    QString fileName = fileDialog->getSaveFileName(this, "Save Annotations", QDir::currentPath(), tr("Annotations (*.annotations)"));
    QJsonDocument json = annotationController.toJSON();
    fileController.saveAnnotations(fileName, json);

    ui->actionSave->setEnabled(true);

}

void ImageAnnotator::on_addClassButton_clicked()
{
    if (ui->addClassInput->text().length() > 0) {
        QString classToAdd = ui->addClassInput->text();
        if (classLabelController.classExists(classToAdd)) {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","A class with that name already exists");
            messageBox.setFixedSize(500,200);
            ui->actionSaveClasses->setEnabled(false);
            return;
        }
        else {
            std::cout << "Adding class" << std::endl;
            classLabelController.addClassLabel(classToAdd);
            QString sortType = ui->classSortType->currentText();
            classLabelController.updateClassesList(ui->classList, sortType);
        }
    }
}

void ImageAnnotator::on_searchImages_textChanged(const QString &arg1)
{
    imageController.displayImages(ui->imageTableView, imageController.searchImages(arg1));
}
