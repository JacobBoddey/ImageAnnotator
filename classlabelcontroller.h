#ifndef CLASSLABELCONTROLLER_H
#define CLASSLABELCONTROLLER_H

#include <linkedlist.h>
#include <classlabel.h>

#include <ui_imageannotator.h>

class ClassLabelController
{

private:

    LinkedList classes;

public:

    ClassLabelController();

    LinkedList getClasses();

    void ClassLabelController::addClassLabel(ClassLabel label);

    void updateClassesList(Ui::ImageAnnotator* ui);

};

#endif // CLASSLABELCONTROLLER_H
