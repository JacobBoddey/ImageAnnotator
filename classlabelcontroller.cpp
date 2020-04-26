#include "classlabelcontroller.h"

#include <iostream>

/**
 * ClassLabelController constructor
 *
 * Initialises the classes list as a new, empty linked list
 */

ClassLabelController::ClassLabelController()
{
    classes = LinkedList();
}

/**
 * Get the classes
 *
 * @return LinkedList* - Pointer to the linked list containing the classes
 */

LinkedList* ClassLabelController::getClasses() {
    return &classes;
}

/**
 * Get a Class Label by its name
 *
 * @param QString - The name of the Class Label
 * @return ClassLabel - The ClassLabel searched for
 */

ClassLabel ClassLabelController::getClassLabel(QString text) {

    Node* current = classes.first();
    while (current != classes.last()->getNext()) {
        if (current->get().getName() == text) {
            return current->get();
        }
        current = current->getNext();
    }
}

/**
 * Checks if a ClassLabel with a given name exists
 *
 * @param QString - The name of the Class Label to search for
 * @return bool - Whether the class exists or not
 */

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

/**
 * Add a Class Label to the list
 *
 * @param ClassLabel - The Class Label to add
 */

void ClassLabelController::addClassLabel(ClassLabel label) {
    classes.append(label);
}

/**
 * Remove a Class Label from the list
 *
 * @param ClassLabel - The Class Label to remove
 */

void ClassLabelController::removeClassLabel(ClassLabel label) {
    classes.remove(label);
}

/**
 * Update the classes in the class list panel
 *
 * @param QListWidget* - The widget to contain the class list
 * @param QString - The sort type, either "Ascending", "Descending", or "Unsorted"
 */

void ClassLabelController::updateClassesList(QListWidget* listWidget, QString sortType) {

    listWidget->clear();

    if (classes.size() == 0) {
        std::cout << "No classes to display" << std::endl;
        return;
    }

    LinkedList* classesList = sortClasses(sortType);

    Node* current = classesList->first();

    while (current != classesList->last()->getNext()) {
        listWidget->addItem(current->get().getName());
        current = current->getNext();
    }

}

/**
 * Sorts the classes list
 *
 * @param QString - Sort type, either "Ascending", "Descending", or "Unsorted"
 * @return LinkedList* - The list of sorted classes
 */

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
