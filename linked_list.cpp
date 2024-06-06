#include <iostream>
#include "linked_list.hpp"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

Node* LinkedList::getHead() {
    return head;
}

Node* LinkedList::getTail() {
    return tail;
}

int LinkedList::getSize() {
    return size;
}

void LinkedList::addNode(float data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void LinkedList::addNode(float data1, float data2) {
    // Adiciona um nó com dois dados (data1 e data2)
    Node* newNode = new Node(data1, data2);
    std::cout << "newNode->data2: " << newNode->data2 << std::endl;
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

Node* LinkedList::removeNodeByIndex(int index) {
    std::cout << "index" << index << std::endl;
    if (index < 0 || index >= size) {
        std::cerr << "Invalid index." << std::endl;
        return nullptr;
    }
    Node* currentNode = head;
    Node* removedNode = nullptr; 
    if (index == 0) {
        head = head->next;
        removedNode = currentNode;
        size--;
        if (!head) {
            tail = nullptr;
        }
        return removedNode; 
    }
    for (int i = 0; i < index - 1; i++) {
        currentNode = currentNode->next;
    }
    Node* nodeToDelete = currentNode->next;
    removedNode = nodeToDelete;
    currentNode->next = nodeToDelete->next;
    if (!currentNode->next) {
        tail = currentNode;
    }
    size--;
    return removedNode; 
}

Node* LinkedList::removeNodeByData(int data) {
    Node* currentNode = head;
    Node* prevNode = nullptr;
    Node* removedNode = nullptr;

    // Percorre a lista até encontrar o nó com o dado especificado
    while (currentNode != nullptr) {
        if (currentNode->data1 == data) {
            // Remove o nó encontrado
            if (prevNode == nullptr) {
                // O nó a ser removido é o primeiro da lista
                head = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }
            if (currentNode == tail) {
                // O nó a ser removido é o último da lista
                tail = prevNode;
            }
            removedNode = currentNode;
            size--;
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    return removedNode;
}

LinkedList LinkedList::sortListDescending() {
    LinkedList sortedList; // Lista para armazenar a lista ordenada
    Node* current = head;

    // Copia os elementos da lista original para a lista ordenada
    while (current != nullptr) {
        sortedList.addNode(current->data1, current->data2); // Adiciona o nó na lista ordenada
        current = current->next;
    }

    // Ordena a lista usando Bubble Sort
    bool swapped;
    Node* ptr;
    Node* lastPtr = nullptr;

    do {
        swapped = false;
        ptr = sortedList.getHead();

        while (ptr->next != lastPtr) {
            if (ptr->data1 < ptr->next->data1) {
                // Troca os valores dos nós se estiverem fora de ordem
                float temp1 = ptr->data1;
                int temp2 = ptr->data2;
                ptr->data1 = ptr->next->data1;
                ptr->data2 = ptr->next->data2;
                ptr->next->data1 = temp1;
                ptr->next->data2 = temp2;
                swapped = true;
            }
            ptr = ptr->next;
        }
        lastPtr = ptr;
    } while (swapped);

    return sortedList; // Retorna a lista ordenada
}

void LinkedList::printList() {
    Node* currentNode = head;
    while (currentNode) {
        std::cout << currentNode->data1 << " ";
        currentNode = currentNode->next;
    }
    std::cout << std::endl;
}