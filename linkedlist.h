#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <classlabel.h>

class Node {

private:

    ClassLabel data = ClassLabel("");
    Node* next;

public:

    Node();

    ClassLabel get();
    void set(ClassLabel cl);

    Node* getNext();
    void setNext(Node* n);

};

class LinkedList
{

private:

    Node *head;
    Node *tail;

public:
    LinkedList();
    LinkedList(const LinkedList& list);

    void append(ClassLabel label);
    void insert(ClassLabel label, int index);

    Node* get(int index);

    Node* first();
    Node* last();

    int size();

    void swap(Node* node1, Node* node2);
    void remove(ClassLabel label);

};

#endif // LINKEDLIST_H
