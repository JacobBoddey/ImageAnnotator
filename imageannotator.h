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

private slots:
    void on_browseClassButton_clicked();

private:

    Ui::ImageAnnotator *ui;

};
#endif // IMAGEANNOTATOR_H
