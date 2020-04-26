#include "linkedlist.h"

#include <iostream>

Node::Node() {

}

/**
 * Obtain the ClassLabel stored in the node
 *
 * @return ClassLabel - The Class Label stored as data
 */

ClassLabel Node::get() {
    return data;
}

/**
 * Sets the Class Label
 *
 * @param ClassLabel - The ClassLabel to set the data attribute to
 */

void Node::set(ClassLabel label) {
    data = label;
}

/**
 * Get the next node
 *
 * @return Node* - pointer to the next node in the linked list
 */

Node* Node::getNext() {
    return next;
}

/**
 * Set the next node
 *
 * @param Node* - The node to be next in the linked list
 */

void Node::setNext(Node* n) {
    next = n;
}

/**
 * Linked List constructor
 *
 * Sets the head and tail to be null - as the list is empty
 */

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

/**
 * Append ClassLabel to list
 *
 * @param ClassLabel - The label to append to the list
 */

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

/**
 * Insert a class label at an index
 *
 * @param ClassLabel - The class label to insert
 * @param int - The index to insert at
 */

void LinkedList::insert(ClassLabel label, int index) {

}

/**
 * Retrieve a node with a given index
 *
 * @param int - The index to retrieve from
 */

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

/**
 * Retrieve the first node
 *
 * @return Node* - The node at the start of the list
 */

Node* LinkedList::first() {
    return head;
}

/**
 * Retrieve the last node
 *
 * @return Node* - The node at the end of the list
 */

Node* LinkedList::last() {
    return tail;
}

/**
 * Get the size of the list
 *
 * @return int - The number of nodes in the list
 */

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

/**
 * Swaps two nodes
 *
 * @param Node* - The first node
 * @param Node* - The second node
 */

void LinkedList::swap(Node* node1, Node* node2) {
    ClassLabel temp = node1->get();
    node1->set(node2->get());
    node2->set(temp);
}

/**
 * Remove a ClassLabel from the list
 *
 * @param ClassLabel - The class label to remove
 */

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
