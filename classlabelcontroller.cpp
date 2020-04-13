#include "classlabelcontroller.h"

#include <iostream>

ClassLabelController::ClassLabelController()
{
    classes = LinkedList();
}

LinkedList* ClassLabelController::getClasses() {
    return &classes;
}

ClassLabel ClassLabelController::getClassLabel(QString text) {

    Node* current = classes.first();
    while (current != classes.last()->getNext()) {
        if (current->get().getName() == text) {
            return current->get();
        }
        current = current->getNext();
    }
}

void ClassLabelController::addClassLabel(ClassLabel label) {
    classes.append(label);
}

void ClassLabelController::removeClassLabel(ClassLabel label) {
    classes.remove(label);
}

void ClassLabelController::updateClassesList(QListWidget* listWidget, QString sortType) {

    listWidget->clear();

    LinkedList* classesList;

    if (getClasses()->size() == 0) {
        return;
    }

    if (sortType == "Unsorted") {
        classesList = getClasses();
    }
    else {
        classesList = sortClasses(sortType);
    }

    Node* current = classesList->first();

    while (current != classesList->last()->getNext()) {
        listWidget->addItem(current->get().getName());
        current = current->getNext();
    }

}

LinkedList* ClassLabelController::sortClasses(QString sortType) {

    for (int i = 0; i < classes.size() - 1; i++) {
        for (int j = 0; j < getClasses()->size() - i - 1; j++) {
            if (sortType == "Descending") {
                if (getClasses()->get(j)->get().getName() < getClasses()->get(j+1)->get().getName()) {
                    getClasses()->swap(getClasses()->get(j), getClasses()->get(j+1));
                }
            }
            else {
                if (getClasses()->get(j)->get().getName() > getClasses()->get(j+1)->get().getName()) {
                    getClasses()->swap(getClasses()->get(j), getClasses()->get(j+1));
                }
            }
        }
    }

    return getClasses();

}
