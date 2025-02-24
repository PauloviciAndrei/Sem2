#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
    if(this->capacity <= 0)
    {
      throw exception();
    }

    this->r = r;
    this->mapSize = 0;
    this->elements = new TElem[this->capacity];
}

///BC- Theta(1), WC- Theta(n), AG- Theta(n)
TValue SortedMap::add(TKey k, TValue v) {
    int i;
    for (i = 0; i < this->mapSize; i++) {
        if (!this->r(this->elements[i].first, k))
            break;
        if (this->elements[i].first == k) {
            TValue oldValue = this->elements[i].second;
            this->elements[i].second = v;
            return oldValue;
        }
    }

    for (int j = this->mapSize; j > i; j--) {
        this->elements[j] = this->elements[j - 1];
    }

    this->elements[i] = make_pair(k, v);
    this->mapSize++;
    return NULL_TVALUE;
}

///BC- Theta(1), WC- Theta(n), AG- Theta(n)
TValue SortedMap::search(TKey k) const {
    for (int i = 0; i < this->mapSize; i++) {
        if (this->elements[i].first == k)
            return this->elements[i].second;
        if (!this->r(this->elements[i].first, k))
            break;
    }
    return NULL_TVALUE;
}

///BC- Theta(1), WC- Theta(n), AG- Theta(n)
TValue SortedMap::remove(TKey k) {
    int i;
    for (i = 0; i < this->mapSize; i++) {
        if (this->elements[i].first == k)
            break;
    }
    if (i == this->mapSize) // Key not found
        return NULL_TVALUE;

    TValue oldValue = this->elements[i].second;
    for (int j = i; j < this->mapSize - 1; j++) {
        this->elements[j] = this->elements[j + 1];
    }
    this->mapSize--;
    return oldValue;
}


int SortedMap::size() const {

    return mapSize;
}

bool SortedMap::isEmpty() const {
	return mapSize == 0;
}

///BC- Theta(1), WC- Theta(n), AG- Theta(n)
void SortedMap::replace(TKey k, TValue oldValue, TValue newValue) {
    for (int i = 0; i < this->mapSize; i++) {
        if (this->elements[i].first == k && this->elements[i].second == oldValue) {
            this->elements[i].second = newValue;
            return;
        }
    }
}


SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	delete[] elements;
}
