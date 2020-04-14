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
    void on_removeClassButton_clicked();

    void on_classSortType_currentTextChanged(const QString &arg1);

    void on_actionSaveClasses_triggered();

    void on_browseImageButton_clicked();

    void on_sortImageReset_clicked();

    void on_sortImageButton_clicked();

private:
    Ui::ImageAnnotator *ui;

};
#endif // IMAGEANNOTATOR_H
