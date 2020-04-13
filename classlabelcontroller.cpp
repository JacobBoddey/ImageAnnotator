#include "classlabelcontroller.h"

ClassLabelController::ClassLabelController()
{
    classes = LinkedList();
}

LinkedList ClassLabelController::getClasses() {
    return classes;
}

void ClassLabelController::addClassLabel(ClassLabel label) {
    classes.append(label);
}

void ClassLabelController::updateClassesList(Ui::ImageAnnotator* ui) {

    ui->classList->clear();

    Node* current = classes.first();

    while (current != classes.last()->getNext()) {
        ui->classList->addItem(current->get().getName());
        current = current->getNext();
    }

}
