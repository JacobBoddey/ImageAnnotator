#ifndef AUTOSAVE_H
#define AUTOSAVE_H
#include <QtCore>

class AutoSave : public QThread
{
public:
    AutoSave();
    void run();

};


#endif // AUTOSAVE_H
