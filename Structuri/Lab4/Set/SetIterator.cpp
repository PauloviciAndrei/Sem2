#include "SetIterator.h"
#include "Set.h"
#include <exception>
#include <iostream>

using namespace std;


SetIterator::SetIterator(const Set& m) : set(m) {
	first();
}


void SetIterator::first() {
	index = 0;
	while (index < set.capacity && set.list[index] == nullptr) {
		index++;
	}
	if (index < set.capacity) {
		node = set.list[index];
	}
	else {
		node = nullptr;
	}
}


void SetIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	node = node->next;
	if (node == nullptr) {
		index++;
		while (index < set.capacity && set.list[index] == nullptr) {
			index++;
		}
		if (index < set.capacity) {
			node = set.list[index];
		}
	}
}


TElem SetIterator::getCurrent() {
	if (!valid()) {
		throw std::exception();
	}
	return node->data;
}

bool SetIterator::valid() const {
	return index < set.capacity && set.list[index] != nullptr;
}

void SetIterator::jumpBackward(int k) {
    if (!this->valid() || k <= 0) {
        throw std::exception();
    }

    if (this->index < k) {
        this->index = this->set.size();
    } else {
        this->index= this->index - k;
        }
}


