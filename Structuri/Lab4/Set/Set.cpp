#include "Set.h"
#include "SetIterator.h"


Set::Set() {
	capacity = 17;
	list = new Node*[capacity];
	for (int i = 0; i < capacity; i++) {
		list[i] = nullptr;
	}
	length = 0;
}

void Set::resize() {
    int oldCapacity = capacity;
    Node** oldList = list;

    capacity *= 2;
    list = new Node*[capacity];

    for (int i = 0; i < capacity; i++) {
        list[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) {
        Node* node = oldList[i];
        while (node != nullptr) {
            Node* nextNode = node->next;

            int newIndex = hash(node->data);
            node->next = list[newIndex];
            list[newIndex] = node;

            node = nextNode;
        }
    }

    delete[] oldList;
}

int Set::hash(TElem elem) const {
	int hash = elem % capacity;
	if (hash < 0) {
		hash += capacity;
	}
	return hash;
}


///BC- Theta(1), WC- Theta(n), AG- Theta(n)
bool Set::add(TElem elem) {
	if ((double)(length + 1) / capacity > 0.75) {
		resize();
	}

	int index = hash(elem);

	if (list[index] != nullptr) {
		Node* node = list[index];
		while (node != nullptr) {
			if (node->data == elem) return false;
			node = node->next;
		}
	}

	Node* newNode = new Node;
	newNode->data = elem;
	newNode->next = list[index]; // if the chain is empty, newNode->next will be nullptr
	list[index] = newNode;
	length++;
	return true;
}


///BC- Theta(1), WC- Theta(n), AG- Theta(n)
bool Set::remove(TElem elem) {
	int index = hash(elem);

	if (list[index] != nullptr) {
		Node* node = list[index];
		Node* prevNode = nullptr;
		while (node != nullptr) {
			if (node->data == elem) {
				if (prevNode == nullptr) {
					list[index] = node->next;
				}
				else {
					prevNode->next = node->next;
				}
				delete node;
				length--;
				return true;
			}
			prevNode = node;
			node = node->next;
		}
	}

	return false;
}

///BC- Theta(1), WC- Theta(n), AG- Theta(n)
bool Set::search(TElem elem) const {
	int index = hash(elem);

	if (list[index] != nullptr) {
		Node* node = list[index];
		while (node != nullptr) {
			if (node->data == elem) return true;
			node = node->next;
		}
	}

	return false;
}


int Set::size() const {
	return length;
}


bool Set::isEmpty() const {
	return length == 0;
}


int Set::difference(const Set& s) {	
	int removedElements = 0;
	SetIterator it = s.iterator();

	while (it.valid()) {
		TElem elem = it.getCurrent();
		if (remove(elem)) removedElements++;
		it.next();
	}

	return removedElements;
}


Set::~Set() {
	for (int i = 0; i < capacity; i++) {
		Node* node = list[i];
		while (node != nullptr) {
			Node* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}
	delete[] list;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


