#ifndef IMAGEANNOTATOR_H
#define IMAGEANNOTATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageAnnotator; }
QT_END_NAMESPACE

class ImageAnnotator : public QMainWindow
{
    Q_OBJECT

public:
    ImageAnnotator(QWidget *parent = nullptr);
    ~ImageAnnotator();

private:
    Ui::ImageAnnotator *ui;
};
#endif // IMAGEANNOTATOR_H
