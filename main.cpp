#include "imageannotator.h"
#include "autosave.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AutoSave saveThread;
    saveThread.start();

    ImageAnnotator w;
    w.show();
    return a.exec();
}
