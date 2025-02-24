#include "SortedSetIterator.h"
#include <exception>
#include <iostream>

using namespace std;

SortedSetIterator::SortedSetIterator( SortedSet& m) : multime(m)
{
    currentIndex = m.head;
}


void SortedSetIterator::first() {
    currentIndex = multime.head;
}


void SortedSetIterator::next() {
    if(!valid())
        throw out_of_range("Iterator out of range");
	currentIndex = currentIndex->next;
}


TElem SortedSetIterator::getCurrent()
{
    if(!valid())
        throw out_of_range("Iter out of range");
    return currentIndex->data;
}

bool SortedSetIterator::valid() const {
    return currentIndex != nullptr;
}

TElem SortedSetIterator::remove() {
    if (!valid())
        throw out_of_range("Iterator is invalid");

    TElem removedData = currentIndex->data;
    Node* nodeToDelete = currentIndex;

    if (currentIndex == multime.head) {
        multime.head = currentIndex->next;
        currentIndex = multime.head;
    } else {
        Node* prevNode = multime.head;
        while (prevNode->next != currentIndex) {
            prevNode = prevNode->next;
        }
        prevNode->next = currentIndex->next;
        currentIndex = currentIndex->next;
    }

    delete nodeToDelete;

    return removedData;
}

