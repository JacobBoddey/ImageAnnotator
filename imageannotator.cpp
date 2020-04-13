#include "imageannotator.h"
#include "ui_imageannotator.h"

ImageAnnotator::ImageAnnotator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageAnnotator)
{
    ui->setupUi(this);
}

ImageAnnotator::~ImageAnnotator()
{
    delete ui;
}

