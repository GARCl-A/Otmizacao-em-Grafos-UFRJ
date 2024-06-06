#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Definição da estrutura do nó
struct Node {
    float data1;
    float data2; // Valor opcional
    Node* next;

    // Construtor para um nó com um valor
    Node(float d1) : data1(d1), data2(0), next(nullptr) {}

    // Construtor para um nó com dois valores
    Node(float d1, float d2) : data1(d1), data2(d2), next(nullptr) {}
};

// Definição da classe LinkedList
class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    Node* getHead();
    Node* getTail();
    int getSize();
    void addNode(float data1);
    void addNode(float data1, float data2);
    Node* removeNodeByIndex(int index);
    Node* removeNodeByData(int data1);
    LinkedList sortListDescending();
    void printList();
};

#endif // LINKEDLIST_H