#ifndef CLASSLABELCONTROLLER_H
#define CLASSLABELCONTROLLER_H

#include <linkedlist.h>
#include <classlabel.h>

#include <QListWidget>

class ClassLabelController
{

private:

    LinkedList classes;

public:

    ClassLabelController();

    LinkedList* getClasses();

    ClassLabel getClassLabel(QString text);

    void addClassLabel(ClassLabel label);

    void removeClassLabel(ClassLabel label);

    void updateClassesList(QListWidget* listWidget, QString sortType = "Unsorted");

    LinkedList* sortClasses(QString sortType);

};

#endif // CLASSLABELCONTROLLER_H
