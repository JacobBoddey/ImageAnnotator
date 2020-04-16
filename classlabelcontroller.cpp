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

bool ClassLabelController::classExists(QString label) {
    Node* current = classes.first();
    if (current == nullptr) {
        return false;
    }
    while (current != classes.last()->getNext()) {
        if (current->get().getName() == label) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

void ClassLabelController::addClassLabel(ClassLabel label) {
    classes.append(label);
}

void ClassLabelController::removeClassLabel(ClassLabel label) {
    classes.remove(label);
}

void ClassLabelController::updateClassesList(QListWidget* listWidget, QString sortType) {

    listWidget->clear();

    if (classes.size() == 0) {
        std::cout << "No classes to display" << std::endl;
        return;
    }

    LinkedList* classesList = sortClasses(sortType);

    Node* current = classesList->first();

    std::cout << "6" << std::endl;

    while (current != classesList->last()->getNext()) {
        std::cout << "7" << std::endl;
        listWidget->addItem(current->get().getName());
        current = current->getNext();
    }

}

LinkedList* ClassLabelController::sortClasses(QString sortType) {

    std::cout << "Sorting...";

    for (int i = 0; i < classes.size() - 1; i++) {
        std::cout << "i = " << i << std::endl;
        for (int j = 0; j < getClasses()->size() - i - 1; j++) {
            std::cout << "j = " << j << std::endl;
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
