#include "linkedlist.h"

#include <iostream>

Node::Node() {

}

ClassLabel Node::get() {
    return data;
}

void Node::set(ClassLabel label) {
    data = label;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node* n) {
    next = n;
}

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

void LinkedList::append(ClassLabel label) {

    Node *newNode = new Node();
    newNode->set(label);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        tail->setNext(newNode);
    }

    tail = newNode;
}

void LinkedList::insert(ClassLabel label, int index) {

}

Node* LinkedList::get(int index) {
    Node* current = head;
    if (index == 0) {
        return current;
    }
    for (int i = 0; i <= index; i++) {
        if (i == index) {
            return current;
        }
        current = current->getNext();
    }
}

Node* LinkedList::first() {
    return head;
}

Node* LinkedList::last() {
    return tail;
}

int LinkedList::size() {

    int size = 0;

    Node* temp;
    temp = head;

    while (temp != tail->getNext()) {
        size++;
        temp = temp->getNext();
    }

    return size;
}

void LinkedList::swap(Node* node1, Node* node2) {
    ClassLabel temp = node1->get();
    node1->set(node2->get());
    node2->set(temp);
}

void LinkedList::remove(ClassLabel label) {

    Node* temp;
    temp = head;

    Node* before = nullptr;

    while (temp != nullptr) {
        if (temp->get().getName() == label.getName()) {
            if (temp == head) {
                //Front of the list (only item in the list)
                head = head->getNext();
                return;
            }
            else if (temp->getNext() == nullptr) {
                //At the end of the list
                tail = before;
                delete temp;
                return;
            }
            else {
                //In the middle of the list
                before->setNext(temp->getNext());
                delete temp;
                return;
            }

        }
        else {
            before = temp;
            temp = temp->getNext();
        }
    }

}
