#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

using namespace std;

SortedSet::SortedSet(Relation r) {
    head = nullptr;
    relation = r;
}

///BC- Theta(1), WC- Theta(n), AG- Theta(n)
bool SortedSet::add(TComp elem) {
    Node* newNode = new Node;
    newNode->data = elem;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return true;
    }

    if (relation(elem, head->data)) {
        if (head->data == elem) {
            delete newNode;
            return false;
        }
        newNode->next = head;
        head = newNode;
        return true;
    }

    Node* current = head;

    while (current->next != nullptr && relation(current->next->data, elem)) {
        if (current->next->data == elem) {
            delete newNode;
            return false;
        }
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return true;
}




///BC- Theta(1), WC- Theta(n), AG- Theta(n)
bool SortedSet::remove(TComp elem) {
    if (head == nullptr) {
        return false;
    }

    if (head->data == elem) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->data != elem) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        previous->next = current->next;
        delete current;
        return true;
    }

    return false;
}


///BC- Theta(1), WC- Theta(n), AG- Theta(n)
bool SortedSet::search(TElem elem) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->data == elem) {
            return true; // Element found
        }

        if (!relation(current->data, elem)) {
            return false; // Element not found
        }
        current = current->next;
    }

    return false; // Element not found
}

///BC- Theta(n), WC- Theta(n), AG- Theta(n)
int SortedSet::size() const {
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

///BC- Theta(1), WC- Theta(1), AG- Theta(1)
bool SortedSet::isEmpty() const {
    return head == nullptr;
}

SortedSetIterator SortedSet::iterator()  {
    return SortedSetIterator(*this);
}

///BC- Theta(n), WC- Theta(n), AG- Theta(n)
SortedSet::~SortedSet() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
